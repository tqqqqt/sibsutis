<?php
	$mysql_data_type = array(1=>'tinyint', 2=>'smallint', 3=>'int', 4=>'float', 5=>'double',
    	7=>'timestamp', 8=>'bigint', 9=>'mediumint', 10=>'date', 11=>'time', 12=>'datetime', 13=>'year',
    	16=>'bit', 253=>'varchar', 254=>'char', 246=>'decimal');

    $mysql_data_flag = array(1=>"not_null", 2=>"prim_key", 4=>"unique_key", 8=>"multiple_key", 16=>"blob",
    	32=>"unsigned", 64=>"zerofill", 128=>"binary", 256=>"enum", 512=>"auto_increment", 1024=>"timestamp");

    $mytable_data_name = array("cnum"=>"Номер покупателя", "cname"=>"Имя покупателя", "city"=>"Город",
    	"rating"=>"Рейтинг", "snum"=>"Номер продавца", "id"=>"Идентификатор", "name"=>"Имя", "address"=>"Адрес",
    	"birthday"=>"Дата рождения", "mail"=>"Почта", "onum"=>"Номер заказа", "amt"=>"Сумма заказа",
    	"odate"=>"Дата заказа", "sname"=>"Имя продовца", "comm"=>"Комиссионные");

    function readFlag($_flag){
    	global $mysql_data_flag;
    	$result="";
    	$curent_raz=1;
    	$temp=intval($_flag);
    	while($temp>0){
    		if(($temp & 1)==1 && isset($mysql_data_flag[$curent_raz])) $result.=" ".$mysql_data_flag[$curent_raz];
    		$curent_raz*=2;
    		$temp=$temp>>1;
    	}
    	return $result;
    }

	function vid_structure($_name_table,$_conn){
	global $mysql_data_type;
		echo "<h4>Структура таблицы $_name_table</h4>";
		$result=mysqli_query($_conn,"select * from $_name_table;");
		$num_fields=mysqli_num_fields($result);
		for($i=0;$i<$num_fields;$i++){
			$properties=mysqli_fetch_field_direct($result,$i);
			$type="";
			if(isset($mysql_data_type[$properties->type])) $type=$mysql_data_type[$properties->type];
			else $type="unknown type";
			$flags=readFlag($properties->flags);
			echo "<p><i>$type $properties->length</i> <b>$properties->name</b> <i>$flags</i></p>";
		}
	}

	function vid_content($_name_table,$_conn){
		echo "<h4>Содержимое таблицы $_name_table</h4>";
		global $mytable_data_name;
		$result=mysqli_query($_conn,"select * from $_name_table;");
		$num_fields=mysqli_num_fields($result);
		echo "<table border='1' cellpadding='2px'>";
		echo "<tr>";
		for($i=0;$i<$num_fields;$i++){
			$name=mysqli_fetch_field_direct($result,$i)->name;
			echo "<th>";
			if(isset($mytable_data_name[$name])) echo "<p align='center'><b>$mytable_data_name[$name]</p>";
			else echo "<p align='center'><b>Нет перевода</p>";
			echo "<p align='center'><b>$name</p>";
			echo "</th>";
		}
		echo "</tr>";
		while($row=mysqli_fetch_row($result)){
			echo "<tr>";
			foreach($row as $elem) echo "<td>$elem</td>";
			echo "</tr>";
		}
		echo "</table>";
	}

	$count_tables=0;
	if(isset($_POST["count_tab"])) $count_tables=$_POST["count_tab"];
	else{
		echo "<a href='z10-01.php'><p>Возврат к выбору таблицы</p></a>";
		die("Error: no count_tables.");
	}
	for($i=0;$i<$count_tables;$i++){
		if(!(isset($_GET["t".$i]))) continue;
		if(isset($_POST["structure".$i]) && $_POST["structure".$i]=="1") vid_structure($_GET["t".$i],$conn);
		if(isset($_POST["content".$i]) && $_POST["content".$i]=="1") vid_content($_GET["t".$i],$conn);
	}
	echo "<hr>";
	echo "<a href='z10-01.php'>Возврат к выбору таблицы</a>";
?>