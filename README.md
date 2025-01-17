# Rapport TP Multi-threading 3A SRI

Marc Guedon - Bastien Lalanne

## Exécution des scripts

Ordre d'exécution :
1. `queuemanager.py`
2. `proxy.py`
3. `./build/low_level`
4. `minion.py`
5. `boss.py`

## Tests de performance

<table>
  <tr>
    <th>Commande utilisée</th>
    <th>Size</th>
    <th>Python Time (s)</th>
    <th>C++ Time (s)</th>
  </tr>
  <tr>
    <td rowspan="5"><code>cmake -B build -S .</code></td>
    <td>100</td>
    <td>0.00043686399999387504</td>
    <td>0.000584581</td>
  </tr>
  <tr>
    <td>500</td>
    <td>0.018299999000191747</td>
    <td>0.034083511</td>
  </tr>
  <tr>
    <td>1000</td>
    <td>0.06520618900140107</td>
    <td>0.871263889</td>
  </tr>
  <tr>
    <td>2000</td>
    <td>0.4005630519998249</td>
    <td>4.502006822</td>
  </tr>
  <tr>
    <td>5000</td>
    <td>4.669737025000131</td>
    <td>69.98614202</td>
  </tr>
  <tr>
    <td rowspan="5"><code>cmake -B build -S . -DCMAKE_BUILD_TYPE=Release</code></td>
    <td>100</td>
    <td>0.0004225420000238955</td>
    <td>0.000780551</td>
  </tr>
  <tr>
    <td>500</td>
    <td>0.010904879000008805</td>
    <td>0.041533481</td>
  </tr>
  <tr>
    <td>1000</td>
    <td>0.06021976800002449</td>
    <td>0.510068399</td>
  </tr>
  <tr>
    <td>2000</td>
    <td>0.34464498799997045</td>
    <td>4.435424932</td>
  </tr>
  <tr>
    <td>5000</td>
    <td>5.440208376999976</td>
    <td>66.416535247</td>
  </tr>
</table>

Les différences de temps de calcul entre Python et C++ peuvent s'expliquer car la librairie python `numpy` qui est utilisée dans le code python, est codée en C et est extrêmement optimisée. De plus, nous avons fait des tests avec l'option de build `-DCMAKE_BUILD_TYPE=Release`, mais aussi sans cette option. Dans la majorité des cas, les tests dont la commande de build avait l'option, ont un temps de calcul plus rapide que les tests sans l'option de build. Cela s'explique car le debug (sans l'option) possède des vérifications que n'a pas la release. Cette dernière est donc logiquement plus rapide.
