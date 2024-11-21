import numpy as np
from sklearn import tree
from sklearn.model_selection import train_test_split as split_data

file_name=input("File name - ")
data=np.genfromtxt(file_name,delimiter=',',skip_header=True)
data_x=data[:,:-1]
data_y=data[:,-1]
learn_data_x, res_data_x, learn_data_y, res_data_y=split_data(data_x,data_y,test_size=0.3,stratify=data_y,random_state=1)

best_res, result_death, result_leaf=0.0, 0, 0
print("Learn:")
for cur_depth in range(2,40):
	for cur_leaf in range(2,40):
		cur_tree=tree.DecisionTreeClassifier(max_depth=cur_depth,min_samples_leaf=cur_leaf)
		cur_tree.fit(learn_data_x,learn_data_y)
		predict=cur_tree.predict(learn_data_x)
		curent_score=0
		for i in range(0,len(predict)):
			if predict[i]==learn_data_y[i]: curent_score+=1
		print(f"Cur_depth={cur_depth}, cur_leaf={cur_leaf}, cur_res={(curent_score/len(learn_data_y))*100:.3f}")
		if best_res<(curent_score/len(learn_data_y))*100:
			best_res=(curent_score/len(learn_data_y))*100
			result_death=cur_depth
			result_leaf=cur_leaf
print(f"Learn result: death={result_death}, leaf={result_leaf}, best_res={best_res:.3f} \n \n")

cur_tree=tree.DecisionTreeClassifier(max_depth=result_death,min_samples_leaf=result_leaf)
cur_tree.fit(learn_data_x,learn_data_y)
predict=cur_tree.predict(res_data_x)
curent_score=0
for i in range(0,len(predict)):
	if predict[i]==res_data_y[i]: curent_score+=1
print(f"Res result: cur_depth={result_death}, cur_leaf={result_leaf}, result_%={(curent_score/len(res_data_y))*100:.3f}, cur_true={curent_score}, data_size={len(res_data_y)}")

for i in range(10):
	learn_data_x, res_data_x, learn_data_y, res_data_y=split_data(data_x,data_y,test_size=0.3,stratify=data_y)
	cur_tree=tree.DecisionTreeClassifier(max_depth=result_death,min_samples_leaf=result_leaf)
	for j in range(3):
		cur_tree.fit(learn_data_x,learn_data_y)
		predict=cur_tree.predict(res_data_x)
		curent_score=0
		for k in range(0,len(predict)):
			if predict[k]==res_data_y[k]: curent_score+=1
		print(f"{i}.{j}. Cur_res={(curent_score/len(res_data_y))*100:.3f}")