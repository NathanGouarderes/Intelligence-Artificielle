poids1 = "C:/Users/natha/Documents/Junia/IA/layers/layer_weightdense.txt"
poids2 = "C:/Users/natha/Documents/Junia/IA/layers/layer_weightdense_1.txt"
poids3 = "C:/Users/natha/Documents/Junia/IA/layers/layer_weightdense_2.txt"
biais1 = "C:/Users/natha/Documents/Junia/IA/layers/layerbiasdense.txt"
biais2 = "C:/Users/natha/Documents/Junia/IA/layers/layerbiasdense_1.txt"
biais3 = "C:/Users/natha/Documents/Junia/IA/layers/layerbiasdense_2.txt"


def count_columns(file_path):
    with open(file_path, "r") as file:
        first_line = file.readline()
        columns = first_line.strip().split()
        return len(columns)


# Remplacez ce chemin par le chemin réel de votre fichier
file_path = "C:/Users/natha/Documents/Junia/IA/layers/layer_weightdense.txt"
colonnes_poids1 = count_columns(poids1)
colonnes_poids2 = count_columns(poids2)
colonnes_poids3 = count_columns(poids3)


print(f"Le nombre de colonnes {poids1} est: {colonnes_poids1}")
print(f"Le nombre de colonnes {poids2} est: {colonnes_poids2}")
print(f"Le nombre de colonnes {poids3} est: {colonnes_poids3}")


def count_lines(file_path):
    with open(file_path, "r") as file:
        return sum(1 for line in file)


# Remplacez ce chemin par le chemin réel de votre fichier
lignes_poids1 = count_lines(poids1)
lignes_poids2 = count_lines(poids2)
lignes_poids3 = count_lines(poids3)
lignes_biais1 = count_lines(biais1)
lignes_biais2 = count_lines(biais2)
lignes_biais3 = count_lines(biais3)

print(f"Le nombre de lignes {poids1} est: {lignes_poids1}")
print(f"Le nombre de lignes {biais1} est: {lignes_biais1}")
print(f"Le nombre de lignes {poids2} est: {lignes_poids2}")
print(f"Le nombre de lignes {biais2} est: {lignes_biais2}")
print(f"Le nombre de lignes {poids3} est: {lignes_poids3}")
print(f"Le nombre de lignes {biais3} est: {lignes_biais3}")
