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
  // Définir le nombre de threads pour le traitement parallèle en utilisant
  // Eigen
  Eigen::setNbThreads(NB_CORES);

  while (true) {
    // Récupération de la tâche depuis le serveur
    cpr::Response response = cpr::Get(cpr::Url{"http://localhost:8000"});

    // Vérifier si la réponse est vide
    if (response.text.empty()) {
      std::cerr << "[LOW_LEVEL] Réponse vide du serveur" << std::endl;
      // On attend un peu avant de réessayer
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    // Vérifier les erreurs réseau
    if (response.error) {
      std::cerr << "[LOW_LEVEL] Erreur réseau : " << response.error.message
                << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    // Vérifier le code HTTP
    if (response.status_code != CODE_SUCCESS) {
      std::cerr << "[LOW_LEVEL] Erreur HTTP : " << response.status_code
                << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    // Parser le JSON
    nlohmann::json data_json;
    try {
      data_json = nlohmann::json::parse(response.text);
    } catch (const nlohmann::json::exception &e) {
      std::cerr << "[LOW_LEVEL] Erreur JSON : " << e.what() << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    // Vérifier la présence des données nécessaires
    if (!data_json.contains("a") || !data_json.contains("b") ||
        !data_json.contains("identifier") || !data_json.contains("size")) {
      std::cerr << "[LOW_LEVEL] Données JSON incomplètes" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    int identifier = data_json["identifier"].get<int>();
    int size = data_json["size"].get<int>();
    double time_val = data_json["time"].get<double>();

    // Créer la tâche depuis le JSON
    Task task = Task::from_json(data_json.dump());

    std::cout << "[LOW_LEVEL] Processus " << getpid() << " a reçu la tâche "
              << identifier << std::endl;

    // Effectuer le travail
    task.work();

    // Poster le résultat (la tâche après execution)
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

    // On peut recommencer la boucle pour traiter une nouvelle tâche
  }

  return 0;
}
