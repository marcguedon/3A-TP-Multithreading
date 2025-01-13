#include "nlohmann/json.hpp"
#include <Eigen/Dense>
#include <chrono>
#include <cpr/cpr.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "task.hpp"

#define CODE_SUCCESS 200
#define NB_CORES 4

int main() {
  Eigen::setNbThreads(NB_CORES);

  while (true) {
    cpr::Response response = cpr::Get(cpr::Url{"http://localhost:8000"});

    if (response.text.empty()) {
      std::cerr << "[LOW_LEVEL] Réponse vide du serveur" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    if (response.error) {
      std::cerr << "[LOW_LEVEL] Erreur réseau : " << response.error.message
                << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    if (response.status_code != CODE_SUCCESS) {
      std::cerr << "[LOW_LEVEL] Erreur HTTP : " << response.status_code
                << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    nlohmann::json data_json;
    try {
      data_json = nlohmann::json::parse(response.text);
    } catch (const nlohmann::json::exception &e) {
      std::cerr << "[LOW_LEVEL] Erreur JSON : " << e.what() << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    if (!data_json.contains("identifier") ||
        !data_json["identifier"].is_number() || !data_json.contains("size") ||
        !data_json["size"].is_number() || !data_json.contains("a") ||
        !data_json.contains("b")) {
      std::cerr << "[LOW_LEVEL] Données JSON incomplètes ou invalides"
                << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    int identifier = data_json["identifier"].get<int>();
    int size = data_json["size"].get<int>();
    std::cout << "[LOW_LEVEL] Size: " << size << std::endl;

    identifier = 2;
    data_json["identifier"] = 2;

    Task task(data_json);

    std::cout << "[LOW_LEVEL] Processus " << getpid() << " a reçu la tâche "
              << identifier << std::endl;

    task.work();

    std::string result_json = task.to_json();
    cpr::Response post_response =
        cpr::Post(cpr::Url{"http://localhost:8000"}, cpr::Body{result_json},
                  cpr::Header{{"Content-Type", "application/json"}});

    if (post_response.status_code == CODE_SUCCESS) {
      std::cout << "[LOW_LEVEL] Résultat de la tâche " << identifier
                << " envoyé avec succès." << std::endl;
    } else {
      std::cerr << "[LOW_LEVEL] Echec de l'envoi du résultat pour la tâche "
                << identifier << ". Code HTTP : " << post_response.status_code
                << std::endl;
    }
  }

  return 0;
}
