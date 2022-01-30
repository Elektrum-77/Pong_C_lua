# Projet PONG

- nom : PONG
- type d'affichage : *graphique* *
- type d'entrer : *lecture clavier* *
- but du projet : réaliser un pong sous forme de librairie du language lua

*(utilisation du framework LOVE2D avec un main écrit en lua)

## INSTALLATION ET LANCEMENT

### LINUX

il faut installer la version dev de libreadline pour que lua puisse compiler

    sudo apt-get libreadline-dev

ensuite il faut avoir une version récente de zip (supporte les options -9 et -q)

    sudo apt install zip
    sudo apt update zip

il ne reste plus qu'a compiler avec :

    make

et de lancer le projet avec :

    make run

### WINDOWS

c'est pas encore fait pour etre facilement déployable sur windows donc pour l'instant c'est difficilement possible

## Pourquoi LOVE2D et lua

J'ai choisi d'utiliser Love2d car je l'ai déjà utilisé pour des projets personnels. Il est facile à mettre en place et à utiliser.

Après un peu de recherche, cela n'avait pas l'air compliqué de faire communiquer les deux languages.

D'autant plus que lua a été conçu pour être implémenté dans un application C. Mais l'inverse est encore plus simple à réaliser.

Meme si l'affichage est en lua il reste important de ne pas oublier que tout le reste du projet doit etre réalisé en C.

Cela m'obligera à séparer l'affichage du *code métier* *.

*(le code qui décrit le fonctionnement d'une partie de pong) 

## compétence

    - créer une librairie en C
    - interaction entre deux languages (le c et le lua)
    - manipulation des strucures
    - manipulation des enumerations
    - manipulation des pointeurs de strucures
    - manipulation des pointeurs de fonctions

# Détails techniques

## Choix de conception

### Le besoin

Un pong est un jeu 1vs1 ou il y a une balle qui se déplace à l'écran. Cette balle est carrée et doit rebondir sur les bords supérieurs et inférieurs de l'écran.
Chaque joueur a à sa disposition une raquette qui peut se déplacer verticalement sur l'écran.
Avec cette raquette, le joueur doit empecher la balle de toucher son coté de l'écran s'il ne veut pas donner un point à son adversaire.

### premier jet pour l'architecture du projet

Il y aura donc besoin d'un structure pour la balle (Ball), une structure pour les raquettes (Pad) et une 
structure pour gérer le tout (Game).

Le jeu n'est pas complexe, il n'y a donc pas besoin d'allouer dynamiquement les différents modules. Les chargés une fois au lancement du jeu suffit. 

#### les structures :

en plus de gérer la Ball et les Pad, Game s'occupera aussi de stocker les bordures du terrains et le score.
- (Ball* ball)
- (Pad* player1, player2)
- (double left, right, up, down)
- (double score1, score2)

La Ball aura une position, une vitesse et un rayon (longueur coté / 2).
- (double x, y)
- (double vx, vy)
- (double raius)

Le Pad aura une position, une vitesse et une longueur.
- (double x, y)
- (double vy)
- (double length)

#### les méthodes :

En premier il faudra initialiser la partie

    void Game_Init(Game *self, Ball *ball, Pad *player1, Pad *player2, double left, double right, double up, double down)

Ensuite il faut pouvoir lancer la balle dans une direction aléatoire.

    void LaunchBall(void)

Il faudra que la balle rebondisse sur les bords et les raquettes

    void Ball_DetectAndBounceOffBallBoundary(Ball *self, double up, double down)
    void Ball_DetectAndBounceOffPad(Ball *self, double pad_x, double pad_y1, double pad_y2)

Ensuite il faudra pouvoir déplacer les raquettes

    void Pad_SetDirection(Pad *self, double vy)

Il faut aussi pouvoir faire avancer les éléments du jeu dans le temps.

    void Game_Update(Game *self, double delta_time)
    void Ball_Update(Ball *self, double delta_time)
    void Pad_Update(Pad *self, double delta_time)


### améliorations proposées

Rendre le projet facilement déployable sur Windows
Faire augmenter la vitesse de la balle a chaque fois qu'elle tape la raquette.
Ajouter un BOT pour remplacer le 2e joueur.
