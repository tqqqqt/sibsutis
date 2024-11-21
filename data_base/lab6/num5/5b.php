<html>
<head>
	<title>Res</title>
</head>
<body>
<?php
	if(isset($_POST["user_name"]) && $_POST["user_name"]!=""){
		$otv=[2,0,2,2];
		$result=0;
		$name=$_POST["user_name"];
		echo "<p>Имя:$name, результат:</p>";
		for($i=1;$i<=count($otv);$i++){
			if($otv[$i-1]==$_POST["q_$i"]){
				$result++;
				echo "<p>Вопрос $i решен верно.</p>";
			}
			else echo "<p>Вопрос $i решен неверно.</p>";
		}
		$all_res=($result/4)*100;
		$tt=count($otv);
		echo "<p> В итоге правильных ответов $result из $tt, это $all_res%</p>";
	}
	else{
		echo "<p>no name no answer</p>";
	}
?>
<hr>
<a href="5a.html">Назад</a>
</body>
</html>