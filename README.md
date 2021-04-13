# Door-Locker
Système de verrouillage/déverrouillage de porte

Simulation sur Proteus Professionnal, d'un système de verrouillage/déverrouillage de porte à l'aide d'un Arduino Uno.
L' utilisateur est invité à insérer un code (nous avons choisi un code de 4 chiffres mais cela peut être modifié par programme). L'utilisateur a 3 tentatives.
Si le code est bon, un LED verte s'allume, signifiant ainsi que la porte est ouverte. Au bout de 10 secondes, la porte se verrouille automatiquement.
Si le code n'est pas bon au bout des 3 tentatives, la porte reste verrouillée, et une alarme se déclenche pendant 10 secondes. L'utilisateur devra attendre la fin de l'alarme avant de  reessayer (Cette durée peut être rallongée).
