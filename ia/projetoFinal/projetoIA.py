# Thauany Moedano #
# RA: 92486 #
# Deep Learning - Modelo de aprendizado #

#1. Import das bibliotecas utilizadas
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation, Flatten
from keras.preprocessing.image import ImageDataGenerator
from keras.layers.convolutional import Convolution2D, MaxPooling2D, ZeroPadding2D
from keras.layers import Conv2D, MaxPooling2D
from keras.layers.noise import GaussianNoise
from keras.layers.normalization import BatchNormalization
from keras.optimizers import SGD,RMSprop,adam
from keras.utils import np_utils
from keras.utils import plot_model
from theano.ifelse import ifelse
from keras import backend as K
K.set_image_dim_ordering('th')

import numpy as np
import h5py
import matplotlib.pyplot as plt
import matplotlib
import os
import theano
from PIL import Image
from numpy import *

from sklearn.utils import shuffle
from sklearn.cross_validation import train_test_split

###########################################################

#2. Ajustando dados - Baseado em tutoriais na internet

#Ajustando tamanho das imagens e canal de cores
img_width = 200
img_height = 200
img_channels = 3

#diretorio de treino e teste
train_data_dir = '/media/sf_datasetShared/dataIA/data5/train'     
validation_data_dir = '/media/sf_datasetShared/dataIA/data5/test'   

#Numero de amostras de treino e teste 
nb_train_samples = 262
nb_validation_samples = 300 

batch_size = 32
nb_classes = 5

if K.image_data_format() == 'channels_first':
    input_shape = (3, img_width, img_height)
else:
    input_shape = (img_width, img_height, 3)

######################################################################

#Gerando o conjunto de treino/teste para o programa
#Indica que vai reescalar, indica o tamanho do recorte e o modo da classe

train_datagen = ImageDataGenerator(rescale=1. / 255)

test_datagen = ImageDataGenerator(rescale=1. / 255)

train_generator = train_datagen.flow_from_directory(
    train_data_dir,
    target_size=(img_width, img_height),
    batch_size=batch_size,
    class_mode='categorical')

validation_generator = test_datagen.flow_from_directory(
    validation_data_dir,
    target_size=(img_width, img_height),
    batch_size=batch_size,
class_mode='categorical')

###########################################################

#3. Definindo parametros inicias da rede neural

#Filtros por convolução
nb_filters = 32
#Tamanho da janela de convolução
nb_conv = 3
#Tamanho da área de pooling 
nb_pool_size = 2 

###########################################################

#4. Define o modelo de rede neural
#Parametros alteraveis
#32 - numero de filtros
#3, 3 - numero de linhas e colunas em cada kernel
#1, 200, 200 - dimensoes (profundidade, largura, altura)

model = Sequential()
 
model.add(Conv2D(nb_filters, (nb_conv, nb_conv), activation="relu", input_shape=(3, 200, 200)))
model.add(Conv2D(nb_filters, (nb_conv, nb_conv), activation="relu", input_shape=(3, 200, 200))) 
model.add(MaxPooling2D(pool_size=(nb_pool_size,nb_pool_size)))

model.add(ZeroPadding2D(padding=(20,20), data_format=None)) 
model.add(Conv2D(nb_filters, (nb_conv, nb_conv), activation="relu", input_shape=(3, 200, 200)))

model.add(Conv2D(nb_filters, (nb_conv, nb_conv), activation="relu", input_shape=(3, 200, 200)))
model.add(MaxPooling2D(pool_size=(nb_pool_size,nb_pool_size)))

model.add(Conv2D(nb_filters, (nb_conv, nb_conv), activation="relu", input_shape=(3, 200, 200)))
model.add(MaxPooling2D(pool_size=(nb_pool_size,nb_pool_size)))

model.add(Dropout(0.35))

model.add(Flatten())

model.add(Dense(nb_classes, activation='sigmoid'))

#mostra o modelo em imagem
plot_model(model, to_file='modelo2.png')

#sumariza o modelo
model.summary()

###########################################################

#5. Compila o modelo
#Parametro alteravel
#loss - mudar funcoes de perda
#optimizer - mudar otimizadores
model.compile(loss='categorical_crossentropy',
              optimizer='adam',
              metrics=['accuracy'])

###########################################################

#Define ciclos de treino e amostras por ciclo 

#6. Treina o modelo
model.fit_generator(
    train_generator,
    steps_per_epoch=nb_train_samples,
    epochs=6,
    )

model.save_weights('peso3.h5')

###########################################################
#7. Testa o modelo

score, acc = model.evaluate_generator(generator=validation_generator,
			steps = nb_validation_samples)
print('Test loss:', score)
print('Test accuracy:', acc)

###########################################################


