<html>
<head><title>add</title></head>
<body>
	<?php
		function addForm($con, $table_name){
			$result=mysqli_query($con,"select * from $table_name;");
			$num_fields=mysqli_num_fields($result);
			echo "<p>Добавление записи в таблицу $table_name:</p>";
			echo "<form action='{$_SERVER['REQUEST_URI']}' method='post'>";
			for($i=0;$i<$num_fields;$i++){
				$name=mysqli_fetch_field_direct($result,$i)->name;
				echo "<p>$name: <input type='text' name='$name'></p>";
			}
			echo "<input type='hidden' name='add_tab' value='$table_name'>";
			echo "<input type='submit' value='Добавить'>";
			echo "</form>";
		}

		function addField($con, $table_name){
			try{
				$result=mysqli_query($con,"select * from $table_name limit 1;");
				$num_fields=mysqli_num_fields($result);
				$values_table_str="";
				$values_str="";
				for($i=0;$i<$num_fields;$i++){
					$prop=mysqli_fetch_field_direct($result,$i);
					$name=$prop->name;
					$len=$prop->length;
					if(strlen($values_table_str)==0) $values_table_str.=$name;
					else $values_table_str.=", ".$name;
					if(!isset($_POST[$name]) || strlen(trim($_POST[$name]))==0) return "Ошибка в поле '$name'. Нет значения или только пробелы.";
					$res_value=trim($_POST[$name]);
					if($len==1 && $res_value!='f' && $res_value!='m') return "Ошибка значения пола. Допустимы только 'f' или 'm'.";
					if($name=="phone" && !preg_match("/\d{9}|\d{10}/",$res_value)) return "Ошибка в поле телефон. Неправильные символы.";
					if($prop->type>=10){
						if(strlen($values_str)==0) $values_str.="'".$res_value."'";
						else $values_str.=", '".$res_value."'";
					}
					else{
						if(strlen($values_str)==0) $values_str.=$res_value;
						else $values_str.=", ".$res_value;
					}
				}
				mysqli_query($con,"insert into $table_name ($values_table_str) values ($values_str);");
			}
			catch(mysqli_sql_exception $exp){
				return $exp->getMessage();
			}
			return "Данные введены правильно. Запись добавлена";
		}

		include("connect.inc");

		try{
			if(isset($_GET["table"]) && $_GET["table"]!=""){
				addForm($conn,$_GET["table"]);
				if(isset($_POST["add_tab"]) && $_POST["add_tab"]!=""){
					$res=addField($conn,$_GET["table"]);
					echo "<p>Результат: $res</p>";
				}
			}
			else die("Нет таблицы...");
		}
		catch(mysqli_sql_exception $exp){
			die("Ошибка: ".$exp);
		}

		include("close.inc");
	?>
</body>