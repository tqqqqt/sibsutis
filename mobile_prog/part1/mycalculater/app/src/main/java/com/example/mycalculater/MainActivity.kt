package com.example.mycalculater

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyRow
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.mycalculater.ui.theme.MycalculaterTheme
import java.util.Vector

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MycalculaterTheme {
                val mainString = remember {mutableStateOf("")}
                Box (modifier = Modifier.fillMaxSize().background(Color.White)) {
                    Column (modifier=Modifier.fillMaxWidth().align(Alignment.BottomCenter),
                        verticalArrangement = Arrangement.Bottom,
                        horizontalAlignment = Alignment.CenterHorizontally){
                        Text(text = mainString.value, fontSize = 40.sp,
                            textAlign = TextAlign.End,
                            modifier = Modifier.fillMaxWidth().padding(vertical=20.dp),
                            fontWeight = FontWeight.Light,
                            lineHeight = 40.sp
                        )
                        Row (modifier=Modifier.fillMaxWidth()){
                            Button(onClick = { mainString.value=changeStr("",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "C", fontSize = 30.sp)
                            }
                            Button(onClick = { if(mainString.value.length>0) mainString.value=mainString.value.substring(0,mainString.value.length-1)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "<-", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("(",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "(", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr(")",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = ")", fontSize = 30.sp)
                            }
                        }
                        Row (modifier=Modifier.fillMaxWidth()){
                            Button(onClick = { mainString.value=changeStr("7",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "7", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("8",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "8", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("9",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "9", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("/",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "/", fontSize = 30.sp)
                            }
                        }
                        Row (modifier=Modifier.fillMaxWidth()){
                            Button(onClick = { mainString.value=changeStr("4",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "4", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("5",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "5", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("6",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "6", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("*",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "*", fontSize = 30.sp)
                            }
                        }
                        Row (modifier=Modifier.fillMaxWidth()){
                            Button(onClick = { mainString.value=changeStr("1",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "1", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("2",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "2", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("3",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "3", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("-",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "-", fontSize = 30.sp)
                            }
                        }
                        Row (modifier=Modifier.fillMaxWidth()){
                            Button(onClick = { mainString.value=changeStr("(-",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "+/-", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("0",mainString.value)},
                                modifier = Modifier.weight(1f)){
                                Text(text = "0", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=mainBody(mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "=", fontSize = 30.sp)
                            }
                            Button(onClick = { mainString.value=changeStr("+",mainString.value)},
                                modifier = Modifier.weight(1f) ){
                                Text(text = "+", fontSize = 30.sp)
                            }

                        }
                    }
                }
            }
        }
    }

    private fun changeStr(addString: String, curString:String):String{
        if(addString=="") return ""
        if(curString=="Error input") return addString
        return curString+addString
    }

    private fun checkPrior(checkString: Char): Int{
        if(checkString=='*' || checkString=='/') return 2
        else if(checkString=='+' || checkString=='-') return 1
        return 0
    }

    private fun checkNeedDrop(resString: MutableList<String>, opString: MutableList<Char>, needOp: Char){
        var lastPrior:Int = 0
        val newPrior:Int = checkPrior(needOp)
        val sizeOp:Int = opString.size
        var tempString:String = ""
        for (i in (sizeOp-1)downTo 0){
            lastPrior=checkPrior(opString[opString.size-1])
            if(lastPrior>=newPrior){
                tempString+=opString[opString.size-1]
                resString.add(tempString)
                tempString=""
                opString.removeAt(opString.size-1)
            }
            else{
                opString.add(needOp)
                return
            }
        }
        opString.add(needOp)
    }

    private fun dropClose(resString: MutableList<String>, opString: MutableList<Char>){
        val stringAdd: Vector<String> = Vector()
        var tempStr:String = ""
        var del:Int = 0
        for(i in (opString.size-1)downTo 0){
            if(opString[i]==')'){
                opString.removeAt(opString.size-1);
                del+=1
            }
            else if(opString[i]=='('){
                opString.removeAt(opString.size-1)
                del+=1
                break
            }
            else{
                tempStr+=opString[i]
                stringAdd.add(tempStr)
                tempStr=""
                opString.removeAt(opString.size-1)
            }
        }
        if(del==2){
            for(i in 0..stringAdd.size-1) resString.add(stringAdd[i])
        }
        else return
    }

    private fun strToInt(needString:String):Int{
        var res:Int=0
        var startPoint:Int=0
        var flagMinus:Int=1
        if(needString[0]=='-'){
            startPoint=1
            flagMinus=-1
        }
        for(i in startPoint..needString.length-1) res=res*10+(needString[i].digitToInt())
        return res*flagMinus
    }

    private fun calculRes(masStr: MutableList<String>):String{
        var i:Int=0
        var masSize=masStr.size
        var tempNum1:Int=0
        var tempNum2:Int=0
        while(i<masSize){
            if(masStr.size==1) break
            if(masStr[i]=="+" || masStr[i]=="-" || masStr[i]=="*" || masStr[i]=="/"){
                tempNum1=strToInt(masStr[i-2])
                tempNum2=strToInt(masStr[i-1])
                if(masStr[i]=="+") tempNum1+=tempNum2
                else if(masStr[i]=="-") tempNum1-=tempNum2
                else if(masStr[i]=="*") tempNum1*=tempNum2
                else if(masStr[i]=="/"){
                    if(tempNum2==0) return "Error input"
                    else tempNum1/=tempNum2
                }
                masStr.removeAt(i)
                masStr.removeAt(i-1)
                masStr[i-2]=tempNum1.toString()
                i-=2
            }
            i+=1
        }
        if(masStr[0][0]=='-') return "("+masStr[0]+")"
        return masStr[0]
    }

    private fun mainBody (programString: String) : String{
        val fullString=programString
        var len=fullString.length
        var tempString: String=""
        var operators = mutableListOf(' ')
        var res = mutableListOf("")
        var findOpen: Int=0
        var numOper:Int=0
        var minusNum:Int=0
        res.removeAt(0)
        operators.removeAt(0)
        for (i in 0 .. len-1){
            if(fullString[i]>='0' && fullString[i]<='9'){
                tempString+=fullString[i]
                numOper=0
            }
            else{
                if(fullString[i]=='-' && minusNum>0) continue
                if(tempString!="") {
                    res.add(tempString)
                    tempString = ""
                }
                if(fullString[i]=='+' || fullString[i]=='-' || fullString[i]=='*' || fullString[i]=='/'){
                    if(numOper>0) return "Error input"
                    numOper+=1
                    if(operators.size>0) checkNeedDrop(res,operators,fullString[i])
                    else operators.add(fullString[i])
                }
                else if(fullString[i]=='('){
                    if(i<len-1 && fullString[i+1]=='-'){
                        minusNum+=1
                        tempString+="-"
                        continue
                    }
                    findOpen+=1
                    operators.add(fullString[i])
                }
                else if(fullString[i]==')'){
                    if(minusNum>0){
                        minusNum-=1
                        continue
                    }
                    if(findOpen<=0) return "Error input"
                    operators.add(fullString[i])
                    dropClose(res,operators)
                    findOpen-=1
                }
                else return "Error input"
            }
        }
        if(findOpen>0) return "Error input"
        if(tempString!="") res.add(tempString)
        tempString=""
        if(operators.size>0){
            for(i in (operators.size-1)downTo 0){
                tempString+=operators[i]
                res.add(tempString)
                tempString=""
                operators.removeAt(i)
            }
        }
        if(res.size==0) return ""
        if(res.size==2) return "Error input"
        return calculRes(res)
    }
}
