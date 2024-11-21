from tensorflow.keras.datasets import imdb
from tensorflow.keras import utils
from sklearn.preprocessing import StandardScaler
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, GaussianDropout, Dropout
from tensorflow.keras.optimizers import SGD
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.preprocessing.sequence import pad_sequences
from keras import regularizers

def vectorize_sequences(sequences, dimension=10000):
    results = np.zeros((len(sequences), dimension))
    for i, sequence in enumerate(sequences):
        results[i, sequence] = 1.
    return results

(x_train, y_train), (x_test, y_test)=imdb.load_data(num_words=10000)
x_train=vectorize_sequences(x_train)
x_test=vectorize_sequences(x_test)
y_train=np.asarray(y_train).astype('float32')
y_test=np.asarray(y_test).astype('float32')

model=Sequential();
model.add(Dense(16, activation='relu', input_shape=(10000,)))
model.add(GaussianDropout(0.2))
model.add(Dense(16, activation='relu'))
model.add(Dense(1, activation='sigmoid'))
model.summary()
model.compile(loss='binary_crossentropy',optimizer='SGD',metrics=['accuracy'])

while True:
  history=model.fit(x_train, y_train, epochs=10, batch_size=64)
  loss, acc=model.evaluate(x_train,y_train,verbose=1)
  if(acc>=0.92): break
  print(f'acc: {acc}')

score=model.predict(x_test)
res=0
for i in range(0,len(score)):
  if (score[i]>0.5 and y_test[i]==1) or (score[i]<=0.5 and y_test[i]==0): res+=1
print("res=",res)
print("size=",len(y_test))
print("acur=",(res/len(y_test))*100)