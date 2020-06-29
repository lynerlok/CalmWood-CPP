# CalmWood-CPP

WINDOWS AND LINUX ONLY. Unfortunaly, no unigine sdk is compatible with macOS.

CPP files for multi agent system module

/!\ data directory is missing to avoid heavy GIT project !


# DEV BUILD INSTRUCTIONS

To build this project with unigine ( development version or release ) :

1. Create an account in Unigine ( follow instructions ) here : https://unigine.com/get-unigine/sign-up-free

2. Get UNIGINE Community SDK

3. Clone or download this repository

4. Download data directory here ( **Link coming soon** )

5. Run unigine browser and sign in

6. Choose "ADD EXISTING" dans choose the path of the cloned repository

7. Modify the project in editor, run build version,... from here

## IDE USER - Kdevelop example - LINUX ONLY 

I make a custom CmakeList.txt in the repository, is usualy the best option to build the project with all the custom components.

In Kdevelop create a new project using this CmakeList.txt

## IDE USER - WINDOWS USERS

You can use visual studio code, usualy windows integration is good with Windows - see the docs here : 

https://developer.unigine.com/en/docs/2.11/code/environment/windows?rlang=cpp

# TO DO LIST

~~1. Enlever "Dead" depuis "Move" ( remove statiety index from move move towards )~~

2. Faire un README

3. Décrémenter satiety index à chaque decision

4. Check RNG, si on prend bien tout les animaux par RUN

5. 1 détection = 1 décision ( éviter les loop si movProba = 100 )

6. Multiple spawn + implémenter correctement spawn GUI

7. Vérifier si protéger territoire est cohérent

8. Affiner proba 

9. GUI déplacement non aléatoire

10. GUI déplacement aléatoire

11. GUI remove dead animal

12. Réduire amplitude en Z

13. Bool isMoving dans GC_environment : while true = déplacement non aléatoire, while false = déplacement aléatoire

14. Birth Date pour changer d'état ( State Date )

15. Supprimer les proba inutiles

16. Texture animal

17. Faire des tiles avec maisons, forêt, marais, bord de marais

18. Interface user

19. Passer tout les agents par RUN ???

20. Animation animal ( vol + se poser )

21. Animation auxiliaire ( attaquer,... ) ==> méthode isTarget( bool, Animal * attaquer )