import pandas as pd
import numpy as np
from sklearn.preprocessing import normalize
from sklearn.model_selection import train_test_split
from sklearn.linear_model import Lars

point_white_wine=0
read_data=pd.read_csv('winequalityN.csv',header=0).fillna(0).values
for i in read_data:
	if i[0]=='white':
		point_white_wine+=1
		i[0]=0
	else: i[0]=1
print(f"Data size = {len(read_data)}")

all_train_result=0
data_x=read_data[point_white_wine:,:12]
data_y=read_data[point_white_wine:,12:]
for i in range(0,len(data_x[0])): data_x[:,i]=normalize([data_x[:,i]])
for i in range(0,10):
	data_x_train, data_x_test, data_y_train, data_y_test=train_test_split(data_x,data_y,test_size=0.3)
	my_model=Lars()
	my_model.fit(data_x_train,np.ravel(data_y_train))
	predict=my_model.predict(data_x_test)
	result=0
	for j in range(0,len(predict)):
		if abs(data_y_test[j]-predict[j])<1: result+=1
	print(f"{i}. Result = {result/len(data_x_test) * 100:.3}, true_count = {result}, all_data = {len(data_y_test)}")
	all_train_result+=(result/len(data_x_test))*100
print(f"Red class: avg_res = {all_train_result/10:.3}")
print("\n \n")

all_train_result=0
data_x=read_data[0:point_white_wine,:12]
data_y=read_data[0:point_white_wine,12:]
for i in range(0,len(data_x[0])): data_x[:,i]=normalize([data_x[:,i]])
for i in range(0,10):
	data_x_train, data_x_test, data_y_train, data_y_test=train_test_split(data_x,data_y,test_size=0.3)
	my_model=Lars()
	my_model.fit(data_x_train,np.ravel(data_y_train))
	predict=my_model.predict(data_x_test)
	result=0
	for j in range(0,len(predict)):
		if abs(data_y_test[j]-predict[j])<1: result+=1
	print(f"{i}. Result = {result/len(data_x_test) * 100:.3}, true_count = {result}, all_data = {len(data_y_test)}")
	all_train_result+=(result/len(data_x_test))*100
print(f"White class: avg_res = {all_train_result/10:.3}")
print("\n \n")

all_train_result=0
data_x=read_data[:,:12]
data_y=read_data[:,12:]
for i in range(0,len(data_x[0])): data_x[:,i]=normalize([data_x[:,i]])
for i in range(0,10):
	data_x_train, data_x_test, data_y_train, data_y_test=train_test_split(data_x,data_y,test_size=0.3)
	my_model=Lars() 
	my_model.fit(data_x_train,np.ravel(data_y_train))
	predict=my_model.predict(data_x_test)
	result=0
	for j in range(0,len(predict)):
		if abs(data_y_test[j]-predict[j])<1: result+=1
	print(f"{i}. Result = {result/len(data_x_test) * 100:.3}, true_count = {result}, all_data = {len(data_y_test)}")
	all_train_result+=(result/len(data_x_test))*100
print(f"All data class: avg_res = {all_train_result/10:.3}")