package com.example.mywidgetl6

import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.Button
import androidx.compose.material3.Checkbox
import androidx.compose.material3.Divider
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableIntState
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.snapshots.SnapshotStateList
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.mywidgetl6.ui.theme.MywidgetL6Theme
import java.net.URL
import kotlin.concurrent.thread

class MainActivity : ComponentActivity() {
    data class site_info(var buyPrise:String?, var sellPrise:String?, var dateInfo:String?, var codeInfo:String?)

    private val colectionItems = mutableStateListOf<site_info>()
    private val curentScreen = mutableIntStateOf(1)
    private val curentSelectDate = mutableIntStateOf(1)
    private val curentDate1 = mutableStateOf("12/02/2024")
    private val curentDate2 = mutableStateOf("12/03/2024")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MywidgetL6Theme {
                when(curentScreen.intValue){
                    1->MainScreen()
                    2->OptionScreen()
                    else->MainScreen()
                }
            }
        }
    }

    override fun onResume() {
        super.onResume()
        val sharedPref = getSharedPreferences("myPref",0)
        val date1=sharedPref.getString("curDate1","")
        val date2=sharedPref.getString("curDate2","")
        curentDate1.value=date1.toString()
        curentDate2.value=date2.toString()
        val temp=mutableIntStateOf(0)
        UpdateInfo(temp)
    }

    override fun onStop() {
        super.onStop()
        SaveInPref()
    }

    @Composable
    private fun MainScreen(){
        val updateProcess = remember { mutableIntStateOf(0) }
        Column(modifier = Modifier.fillMaxSize()){
            Button(onClick = { curentScreen.intValue=2 }) {
                Text(text = "Настройки", modifier = Modifier.weight(1f), fontSize = 20.sp)
            }
            Button(onClick = {
                UpdateInfo(updateProcess)
                UpdateWidgetInfo(curentSelectDate.intValue)
            }) {
                Text(text = if(updateProcess.intValue==0) "Обновить" else "Обновление...", modifier = Modifier.weight(1f), fontSize = 20.sp)
            }
            Row (modifier=Modifier.fillMaxWidth()){
                Text(text = "Дата", modifier=Modifier.weight(1f), fontSize = 15.sp)
                Text(text = "Код", modifier=Modifier.weight(1f), fontSize = 15.sp)
                Text(text = "Цена покупки", modifier=Modifier.weight(1f), fontSize = 15.sp)
                Text(text = "Цена продажи", modifier=Modifier.weight(1f), fontSize = 15.sp)
            }
            Divider()
            LazyColumn {
                items(colectionItems) { item ->
                    Row(modifier = Modifier
                        .fillMaxWidth()
                        .padding(vertical = 10.dp)) {
                        Text(
                            text = item.dateInfo!!,
                            modifier = Modifier.weight(1f),
                            fontSize = 15.sp
                        )
                        Text(
                            text = item.codeInfo!!,
                            modifier = Modifier.weight(1f),
                            fontSize = 15.sp
                        )
                        Text(
                            text = item.buyPrise!!,
                            modifier = Modifier.weight(1f),
                            fontSize = 15.sp
                        )
                        Text(
                            text = item.sellPrise!!,
                            modifier = Modifier.weight(1f),
                            fontSize = 15.sp
                        )
                    }
                }
            }
        }
    }

    @Composable
    private fun OptionScreen() {
        val date11 = remember { mutableStateOf("") }
        val date12 = remember { mutableStateOf("") }
        val date13 = remember { mutableStateOf("") }
        val date21 = remember { mutableStateOf("") }
        val date22 = remember { mutableStateOf("") }
        val date23 = remember { mutableStateOf("") }
        val checkBox1 = remember { mutableStateOf(true) }
        val checkBox2 = remember { mutableStateOf(false) }
        if(curentSelectDate.value==1){
            checkBox1.value=true
            checkBox2.value=false
        }
        else{
            checkBox2.value=true
            checkBox1.value=false
        }
        Box {
            Column {
                Button(onClick = {
                    if (CheckInput(
                            date11.value,
                            date12.value,
                            date13.value
                        ) == 4 && CheckInput(date21.value, date22.value, date23.value) == 4
                    ) curentScreen.intValue=1
                    else if (CheckInput(
                            date11.value,
                            date12.value,
                            date13.value
                        ) == 1 && CheckInput(date21.value, date22.value, date23.value) == 1
                    ){
                        curentDate1.value=(date11.value+"/"+date12.value+"/"+date13.value)
                        curentDate2.value=(date21.value+"/"+date22.value+"/"+date23.value)
                        SaveInPref()
                        UpdateWidgetInfo(curentSelectDate.intValue)
                        curentScreen.intValue = 1
                    }
                }) {
                    Text(text = "Готово", modifier = Modifier.weight(1f), fontSize = 20.sp)
                }
                Text(
                    text = "Первая дата (Д.М.Г. 01/01/2024)",
                    fontSize = 20.sp
                )
                Row(modifier = Modifier.fillMaxWidth()) {
                    OutlinedTextField(
                        value = date11.value,
                        onValueChange = { text -> date11.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        modifier = Modifier.weight(1f)
                    )
                    OutlinedTextField(
                        value = date12.value,
                        onValueChange = { text -> date12.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        modifier = Modifier.weight(1f)
                    )
                    OutlinedTextField(
                        value = date13.value,
                        onValueChange = { text -> date13.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        modifier = Modifier.weight(1f)
                    )
                }
                Text(
                    text = "Вторая дата (Д.М.Г. 01/01/2024)",
                    fontSize = 20.sp
                )
                Row(modifier = Modifier.fillMaxWidth()) {
                    OutlinedTextField(
                        value = date21.value,
                        onValueChange = { text -> date21.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        modifier = Modifier.weight(1f)
                    )
                    OutlinedTextField(
                        value = date22.value,
                        onValueChange = { text -> date22.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        modifier = Modifier.weight(1f)
                    )
                    OutlinedTextField(
                        value = date23.value,
                        onValueChange = { text -> date23.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        modifier = Modifier.weight(1f)
                    )
                }
                Row(modifier=Modifier.fillMaxWidth()){
                    Text(text = "Первая дата")
                    Checkbox(checked = checkBox1.value, onCheckedChange = { check ->
                        checkBox1.value=check
                        checkBox2.value=!check
                        curentSelectDate.intValue=1
                    } )
                }
                Row(modifier=Modifier.fillMaxWidth()){
                    Text(text = "Последняя дата")
                    Checkbox(checked = checkBox2.value, onCheckedChange = { check ->
                        checkBox2.value=check
                        checkBox1.value=!check
                        curentSelectDate.intValue=2
                    } )
                }
            }
        }
    }

    //----------------

    private fun <T> SnapshotStateList<T>.swapList(newList: List<T>){
        clear()
        addAll(newList)
    }

    private fun SaveInPref(){
        val sharedPref=getSharedPreferences("myPref", 0)
        sharedPref.edit().clear()
        with(sharedPref.edit()){
            putString("curDate1",curentDate1.value)
            putString("curDate2",curentDate2.value)
            apply()
        }
    }

    private fun CheckInput(day:String, mounth:String, year:String):Int{
        if(day.isBlank() && mounth.isBlank() && year.isBlank()) return 4
        if(day.isBlank() || mounth.isBlank() || year.isBlank()) return 0
        val tempDay=day.toInt()
        val tempMounth=mounth.toInt()
        val tempYear=year.toInt()
        if(tempDay<=0 || tempDay>31 || day.length!=2) return 0
        if(tempMounth<=0 || tempMounth>12 || mounth.length!=2) return 0
        if(tempYear<2000 || tempYear>2024 || year.length!=4) return 0
        return 1
    }

    private fun WriteToPref(numPos:Int, tempStr:String){
        val sharedPref=getSharedPreferences("myPref",0)
        with(sharedPref.edit()){
            putString("widgetInfo${numPos.toString()}",tempStr)
            apply()
        }
    }

    private fun UpdateInfo(tempProcess:MutableIntState){
        thread {
            tempProcess.intValue=1
            var tempList :List<site_info> = listOf()
            val siteInfo =
                URL("https://www.cbr.ru/scripts/xml_metall.asp?date_req1="+curentDate1.value+"&date_req2="+curentDate2.value).readText()
            val buyPattern = Regex("<Buy>([\\d,]*)</Buy>")
            val sellPattern = Regex("<Sell>([\\d,]*)</Sell>")
            val dataPattern = Regex("Record Date=\"(\\d{2}\\.\\d{2}\\.\\d{4})\"")
            val codePattern = Regex("Code=\"(\\d+)\"")
            val buyMatchResult = buyPattern.findAll(siteInfo)
            val sellMatchResult = sellPattern.findAll(siteInfo)
            val dataMatchResult = dataPattern.findAll(siteInfo)
            val codeMatchResult = codePattern.findAll(siteInfo)
            var i=0
            while(true){
                if(i>=codeMatchResult.count()) break
                val buyValue = buyMatchResult.elementAt(i).groupValues
                val sellValue = sellMatchResult.elementAt(i).groupValues
                val dataValue = dataMatchResult.elementAt(i).groupValues
                val codeValue = codeMatchResult.elementAt(i).groupValues
                if (buyValue != null && sellValue != null) {
                    val temp = site_info(buyValue[1], sellValue[1], dataValue[1], codeValue[1])
                    tempList+=temp
                } else break
                i+=1
                colectionItems.swapList(tempList)
            }
            tempProcess.intValue=0
        }
    }

    private fun UpdateWidgetInfo(needGroud:Int){
        thread {
            val siteInfo=URL("https://www.cbr.ru/scripts/xml_metall.asp?date_req1="+curentDate1.value+"&date_req2="+curentDate2.value).readText()
            val buyPattern = Regex("<Buy>([\\d,]*)</Buy>")
            val sellPattern = Regex("<Sell>([\\d,]*)</Sell>")
            val buyMatchResult = buyPattern.findAll(siteInfo)
            val sellMatchResult = sellPattern.findAll(siteInfo)
            var i=0
            var find=0
            var tempFind=0
            if(needGroud==1){
                i=0
                find=0
            }
            else{
                i=buyMatchResult.count()-1
                find=1
            }

            while(true){
                val buyValue = buyMatchResult.elementAt(i).groupValues
                val sellValue = sellMatchResult.elementAt(i).groupValues
                if (buyValue != null && sellValue != null) {
                    val tempStr="Покупка=${buyValue[1]}\nПродажа=${sellValue[1]}"
                    Log.e("tempCheck","$tempStr")
                    if(needGroud==1) WriteToPref(find,tempStr)
                    else WriteToPref(4-find,tempStr)
                } else break
                if(needGroud==1) i+=1
                else i-=1
                find+=1
                tempFind+=1
                if(tempFind==4) break
            }
        }
    }
}