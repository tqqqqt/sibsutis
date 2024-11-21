package com.example.tabslab

import androidx.compose.foundation.Image
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Button
import androidx.compose.material3.Divider
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp

@Composable
fun ListPage(textLists: MutableList<String>){
    val textField = remember { mutableStateOf("") }
    Column {
        Row {
            OutlinedTextField(value = textField.value, onValueChange = { text -> textField.value = text}, modifier=Modifier.weight(1f))
            Spacer(modifier = Modifier.width(16.dp))
            Button(onClick = {
                if(textField.value.isNotBlank()){
                    textLists.add(textField.value)
                    textField.value=""
                }
            }) {
                Text(text="add", fontSize = 10.sp)
            }
        }
        LazyColumn{
            items(textLists) { textList ->
                Row (verticalAlignment = Alignment.CenterVertically) {
                    Image(painter = painterResource(id = R.drawable.ic_launcher_foreground),contentDescription = "simple picture", modifier = Modifier.size(20.dp).border(1.dp,
                        Color.Black))
                    Text(textList,modifier=Modifier.padding(10.dp))
                }
                Divider()
            }
        }
    }
}