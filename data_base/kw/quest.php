<html>
<head><title>Quest</title></head>
<body>
	<?php
		function printForm(){
			echo "<form action='{$_SERVER['REQUEST_URI']}' method='post'>";
			echo "<p>Начальная дата: <input type='date' name='d1' min='1980-01-01' max='2050-01-01'/></p>";
			echo "<p>Конечная дата: <input type='date' name='d2' min='1980-01-01' max='2050-01-01'/></p>";
			echo "<input type='hidden' name='tab_quest' value='ok'>";
			echo "<input type='submit' value='Найти'>";
			echo "</form>";
		}

		function q3($con, $date_start, $date_end){
			if(strlen(trim($date_start))==0 || strlen(trim($date_end))==0){
				echo "<p>Поля дат пустые</p>";
				return;
			}
			if($date_start>$date_end){
				echo "<p>Начальная дата больше конечной</p>";
				return;
			}
			$result=mysqli_query($con,"select name from master where mnum in (select mnum from ord where odate between '$date_start' and '$date_end');");
			echo "<p>Мастера работающие с $date_start по $date_end:</p>";
			echo "<ul>";
			while($row=mysqli_fetch_row($result)) echo "<li>$row[0]</li>";
			echo "</ul>";
		}


		include("connect.inc");

		if(!isset($_GET["target"]) || ($_GET["target"]!="z1" && $_GET["target"]!="z2" && $_GET["target"]!="z3")) die("Нет понимания задания.");
		if($_GET["target"]=="z1"){
			$result=mysqli_query($conn,"select address from salon where snum in (select snum from ord group by snum having count(*)=(select max(count_ord) from (select snum, count(*) as count_ord from ord group by snum) as tmp));");
			echo "<p>Адреса самых популярных салонов:</p>";
			echo "<ul>";
			while($row=mysqli_fetch_row($result)) echo "<li>$row[0]</li>";
			echo "</ul>";
		}
		else if($_GET["target"]=="z2"){
			$result=mysqli_query($conn,"select t1.name, count(t2.onum) from master t1 left join ord t2 on t1.mnum=t2.mnum group by t1.mnum order by count(t2.onum) desc;");
			echo "<p>Мастера и количество выполненых заказов:</p>";
			echo "<ul>";
			while($row=mysqli_fetch_row($result)) echo "<li>$row[0] с $row[1] заказами</li>";
			echo "</ul>";
		}
		else if($_GET["target"]=="z3"){
			printForm();
			if(isset($_POST["tab_quest"]) && $_POST["tab_quest"]!="") q3($conn,$_POST["d1"],$_POST["d2"]);
		}

		include("close.inc");
	?>
</body>
</html>