# C

##Compilation :
```gcc hasheur.c -o t3c```

##Avec Docker
On doit d'abord changer le nom du dictionnaire par dico.txt ou modifiez le dans le Dockerfile.
Ensuite vous buildez votre image.

```sudo docker build -t compilateur_c .```

On peut ensuite rentrer dans le conteneur pour utiliser le binaire
```sudo docker run -it compilateur_c```

##Fonctionnement:

- Deux modes : L et G 


