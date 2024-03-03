import tensorflow as tf
import numpy as np
import os
import matplotlib

matplotlib.use("tkAgg")
import matplotlib.pyplot as plt

from tensorflow.keras.utils import to_categorical

# Définition des chemins des dossiers contenant les images d'entraînement et de test
train_folder = "C:/Users/natha/Documents/Junia/IA/nathan/trainDataset"  # "/home/nathan/trainDataset"
test_folder = (
    "C:/Users/natha/Documents/Junia/IA/nathan/testDataset"  # "/home/nathan/testDataset"
)


# Fonction pour charger les images
def load_images(folder_path, nb_digit, nb_version):
    images = []
    labels = []
    for digit in range(nb_digit):
        for version in range(nb_version):
            image_path = os.path.join(folder_path, f"{digit}_{version}.bmp")
            image = tf.keras.preprocessing.image.load_img(
                image_path, color_mode="grayscale", target_size=(28, 28)
            )
            image = tf.keras.preprocessing.image.img_to_array(image)
            images.append(image)
            labels.append(digit)
    return np.array(images), np.array(labels)


epoch = 23


# Chargement des images d'entraînement
x_train, y_train = load_images(train_folder, 10, 20)

# Chargement des images de test sans normalisation
x_test, y_test = load_images(test_folder, 10, 3)

# Normalisation des images de test
x_test /= 255.0

# One-hot encodage des étiquettes
y_train_onehot = to_categorical(y_train, num_classes=10)
y_test_onehot = to_categorical(y_test, num_classes=10)

# Création du modèle
model = tf.keras.models.Sequential(
    [
        tf.keras.layers.Flatten(input_shape=(28, 28, 1)),
        tf.keras.layers.Dense(
            1176,
            activation="relu",
            kernel_initializer=tf.keras.initializers.GlorotNormal(),
        ),
        # tf.keras.layers.Dropout(0.3),
        tf.keras.layers.Dense(
            256,
            activation="relu",
            kernel_initializer=tf.keras.initializers.GlorotNormal(),
        ),
        # tf.keras.layers.Dropout(0.2),
        tf.keras.layers.Dense(
            10,
            activation="softmax",
            kernel_initializer=tf.keras.initializers.GlorotNormal(),
        ),
    ]
)

# Compilation du modèle avec categorical_crossentropy
model.compile(optimizer="adam", loss="categorical_crossentropy", metrics=["accuracy"])

# Entraînement du modèle avec les étiquettes one-hot
history = model.fit(x_train, y_train_onehot, epochs=epoch, batch_size=25)

# Évaluation du modèle avec les étiquettes one-hot
eval_loss, eval_acc = model.evaluate(x_test, y_test_onehot, batch_size=1, verbose=2)
print("Accuracy: ", eval_acc * 100)

# sauvegarde du model
model.save("bernard3")


# Prédiction sur les données de test
predictions = model.predict(x_test)
image_test_c = "C:/Users/natha/Documents/Junia/IA/C++/5_0.bmp"
image_test = tf.keras.preprocessing.image.load_img(
    image_test_c, color_mode="grayscale", target_size=(28, 28)
)
image_test = tf.keras.preprocessing.image.img_to_array(image_test)
image_test /= 255.0
predictions_test = model.predict(np.array([image_test]))
predictions_test_label = np.argmax(predictions_test)
print("La prédiction est : ", predictions_test_label)

# Affichage des prédictions dans le terminal
for i in range(len(x_test)):
    true_label = y_test[i]
    predicted_label = np.argmax(predictions[i])
    print(f"Image {i+1}: Label réel: {true_label}, Prédiction: {predicted_label}")

# Enregistrement des biais et des poids dans des fichiers txt
for i, layer in enumerate(model.layers):
    array = layer.get_weights()
    if len(array) != 0:
        w1, b1 = layer.get_weights()
        np.savetxt("layers/layer_weight" + layer.name + ".txt", w1)
        print("Le layer est : ", layer.name, w1)
        np.savetxt("layers/layerbias" + layer.name + ".txt", b1)
