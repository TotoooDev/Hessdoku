# Conventions d'écriture

- Une instruction par ligne.
- Découper les lignes trop longues (128 caractères maximum).
- Les fonctions et variables doivent être écrites en `camelCase` et en anglais correct. Les abbréviations sont tolérée si elles sont évidentes (`coordinates` peut devenir `coords` par exemple).
- Les types prennent `T_` en préfixe, sont écrits en `camelCase` et en anglais correct : `T_CoolTypeName`.
- Les parenthèses sont :
    - Pour les fonctions, collées au nom de la fonction : `void coolFunction(int coolParam);`.
    - Pour les instructions de contrôle de flot (`for`, `if`, `switch`, ...), séparées par l'instruction avec un espace : `if (coolCondition)`.
- Les accolades sont sur une nouvelle ligne :
```c
    while (coolCondition)
    {
        doSomething();
    }
```
- Dans le cas où on n'écrit qu'une instruction après un `if`, `for` et `while`, il ne faut pas mettre d'accolade :
```c
if (coolCondition)
    doSomething();
```
