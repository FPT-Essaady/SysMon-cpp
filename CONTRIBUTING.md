# CONTRIBUTING.md

\* Les etapes en bref :

Cloner et configurer le projet -
faire une Pull Request -
Le Nommage des branches et conventions de commit -
formater et tester le code avant la PR. \*

## 1. Comment cloner et configurer le projet

Pour cloner le projet sur votre machine, suivez ces étapes :

1. **Installez Git (si vous ne l'avez pas déjà)** :

   - Vous pouvez télécharger Git depuis [ici](https://git-scm.com/). // faire Crtl+ clicker sur le lien .

2. **Clonez le projet** :

   - Ouvrez le terminal et tapez cette commande pour cloner le projet :

     ```bash
     git clone https://github.com/username/repository.git
     ```

     Remplacez `username` et `repository` par le nom d'utilisateur et le nom du dépôt.

     // exemple : https://github.com/sofyanehb/SysMon-cpp.git

3. **Entrez dans le projet** :
   - Une fois le clonage terminé, entrez dans le dossier du projet avec :
     ```bash
     cd repository
     ```

## 2. Comment faire une Pull Request

1. **Créez une nouvelle branche** :

   - Après être entré dans le projet, vous devez créer une nouvelle branche :
     ```bash
     git checkout -b feature-name
     ```
     Remplacez `feature-name` par un nom de branche approprié pour la fonctionnalité que vous allez ajouter.

2. **Modifiez le code** :

   - Effectuez les modifications souhaitées sur le code.

3. **Enregistrez les modifications** :

   - Enregistrez vos modifications avec `add` et `commit` :
     ```bash
     git add .
     git commit -m "Description de la modification"
     ```

4. **Poussez les modifications (Push)** :

   - Poussez vos modifications vers la branche sur le dépôt distant :
     ```bash
     git push origin feature-name
     ```

5. **Ouvrir une Pull Request** :
   - Après avoir poussé vos modifications, vous pouvez ouvrir une PR sur GitHub :
     - Accédez au dépôt sur GitHub et vous recevrez une notification pour ouvrir une Pull Request.
     - Cliquez sur "New Pull Request" et suivez les étapes pour expliquer vos modifications.

## 3. Nommage des branches et conventions de commit

1. **Nommer les branches** :

   - Il est important de donner des noms de branches clairs pour indiquer ce que vous faites dans chaque branche. Par exemple :
     - `feature/nom-de-la-fonctionnalité`
     - `bugfix/correction-du-bug`
     - `hotfix/correction-urgente`

2. **Conventions de commit** :
   - Le format des commits doit être le suivant :
     - `type: brève description de la modification`
     - Exemples :
       - `feat: ajout d'une nouvelle fonctionnalité de recherche`
       - `fix: correction d'un bug dans la recherche`
       - `docs: mise à jour de la documentation`
       - `style: correction de la mise en forme du code`

## 4. Comment formater et tester le code avant la PR

1. **Formater le code** :

   - Il est recommandé d'utiliser l'outil **Prettier** pour formater votre code avant d'ouvrir une PR. Vous pouvez l'installer et l'utiliser comme suit :
     - **Installer Prettier** :
       ```bash
       npm install --save-dev prettier
       ```
     - **Lancer Prettier** :
       ```bash
       npx prettier --write .
       ```

2. **Tester le code** :
   - Il est également recommandé de lancer les tests avant d'ouvrir une PR :
     - Si vous utilisez **Jest**, par exemple, lancez :
       ```bash
       npm test
       ```
