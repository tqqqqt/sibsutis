package com.example.dbprog5

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.MoreVert
import androidx.compose.material3.Button
import androidx.compose.material3.Divider
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableIntState
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.dbprog5.ui.theme.Dbprog5Theme

class MainActivity : ComponentActivity() {
    private var sqlFunc: DataBaseFunc = DataBaseFunc(this)
    private val colectionItems = mutableListOf<DataBaseFunc.DBItem>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val curentScreen = mutableIntStateOf(1)
        val curentSortField = mutableStateOf("")
        setContent {
            Dbprog5Theme {
                when (curentScreen.intValue) {
                    1 -> ScreenList(curentScreen, curentSortField)
                    2 -> ScreenAdd(curentScreen, curentSortField.value)
                    3 -> ScreenDelete(curentScreen, curentSortField.value)
                }
            }
        }
    }

    override fun onResume() {
        super.onResume()
        sqlFunc.OpenDataBase()
        sqlFunc.GetColection(colectionItems, "_id")
    }

    override fun onDestroy() {
        super.onDestroy()
        sqlFunc.CloseDataBase()
    }

    @Composable
    private fun ScreenAdd(curentScreen: MutableIntState, curentSort: String) {
        val textName = remember { mutableStateOf("") }
        val textWeight = remember { mutableStateOf("") }
        val textHeight = remember { mutableStateOf("") }
        val textAge = remember { mutableStateOf("") }
        Box(modifier = Modifier.fillMaxSize()) {
            Column(
                modifier = Modifier
                    .fillMaxHeight()
                    .fillMaxWidth()
            ) {
                Row(modifier = Modifier.fillMaxWidth()) {
                    Text(text = "Имя")
                    Spacer(modifier = Modifier.width(16.dp))
                    OutlinedTextField(
                        value = textName.value,
                        onValueChange = { text -> textName.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Text),
                        modifier = Modifier.weight(1f)
                    )
                }
                Row(modifier = Modifier.fillMaxWidth()) {
                    Text(text = "Вес")
                    Spacer(modifier = Modifier.width(16.dp))
                    OutlinedTextField(
                        value = textWeight.value,
                        onValueChange = { text -> textWeight.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        modifier = Modifier.weight(1f)
                    )
                }
                Row(modifier = Modifier.fillMaxWidth()) {
                    Text(text = "Рост")
                    Spacer(modifier = Modifier.width(16.dp))
                    OutlinedTextField(
                        value = textHeight.value,
                        onValueChange = { text -> textHeight.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        modifier = Modifier.weight(1f)
                    )
                }
                Row(modifier = Modifier.fillMaxWidth()) {
                    Text(text = "Возраст")
                    Spacer(modifier = Modifier.width(16.dp))
                    OutlinedTextField(
                        value = textAge.value,
                        onValueChange = { text -> textAge.value = text },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        modifier = Modifier.weight(1f)
                    )
                }
                Button(onClick = {
                    if(textName.value.isNotBlank() && textWeight.value.isNotBlank() && textHeight.value.isNotBlank() && textAge.value.isNotBlank()) {
                        sqlFunc.AddItem(
                            textName.value,
                            textWeight.value.toInt(),
                            textHeight.value.toInt(),
                            textAge.value.toInt()
                        )
                        sqlFunc.GetColection(colectionItems, curentSort)
                    }
                }, modifier = Modifier.fillMaxWidth()) {
                    Text(text = "Добавить", fontSize = 20.sp)
                }
                Button(onClick = {
                    if(textName.value.isNotBlank() && textWeight.value.isNotBlank() && textHeight.value.isNotBlank() && textAge.value.isNotBlank()) {
                        sqlFunc.AddItem(
                            textName.value,
                            textWeight.value.toInt(),
                            textHeight.value.toInt(),
                            textAge.value.toInt()
                        )
                        sqlFunc.GetColection(colectionItems, curentSort)
                        curentScreen.intValue = 1
                    }
                }, modifier = Modifier.fillMaxWidth()) {
                    Text(text = "Добавить и вернуться", fontSize = 20.sp)
                }
                Button(onClick = {
                    textName.value = ""
                    textWeight.value = ""
                    textHeight.value = ""
                    textAge.value = ""
                }, modifier = Modifier.fillMaxWidth()) {
                    Text(text = "Очистить", fontSize = 20.sp)
                }
                Button(
                    onClick = { curentScreen.intValue = 1 },
                    modifier = Modifier.fillMaxWidth()
                ) {
                    Text(text = "Назад", fontSize = 20.sp)
                }
            }
        }
    }

    @Composable
    private fun ScreenDelete(curentScreen: MutableIntState, curentSort: String) {
        val countDel = remember { mutableIntStateOf(0) }
        Box(modifier = Modifier.fillMaxSize()) {
            Column(
                modifier = Modifier
                    .fillMaxHeight()
                    .fillMaxWidth()
            ) {
                Button(onClick = {
                    if (countDel.intValue > 0) {
                        sqlFunc.DelItem( colectionItems)
                        sqlFunc.GetColection( colectionItems, curentSort)
                    }
                    curentScreen.intValue = 1
                }) {
                    Text(text = if (countDel.intValue > 0) "Удалить" else "Назад")
                }
                LazyColumn {
                    items(colectionItems) { item ->
                        val colorBack = remember { mutableStateOf(Color.White) }
                        Row(modifier = Modifier.fillMaxWidth().background(colorBack.value)) {
                            IconButton(onClick = {
                                item.deletePoint = 1 - item.deletePoint
                                if (item.deletePoint == 1) {
                                    countDel.intValue += 1
                                    colorBack.value = Color.Red
                                } else {
                                    countDel.intValue -= 1
                                    colorBack.value = Color.White
                                }
                            }) {
                                Icon(
                                    imageVector = Icons.Default.Delete,
                                    contentDescription = "Удалить"
                                )
                            }
                            Text(text = item.name, modifier = Modifier.weight(2f), fontSize = 20.sp)
                            Text(
                                text = item.weight.toString(),
                                modifier = Modifier.weight(1f),
                                fontSize = 20.sp
                            )
                            Text(
                                text = item.height.toString(),
                                modifier = Modifier.weight(1f),
                                fontSize = 20.sp
                            )
                            Text(
                                text = item.age.toString(),
                                modifier = Modifier.weight(1f),
                                fontSize = 20.sp
                            )
                        }
                    }
                }
            }
        }
    }

    @Composable
    private fun ScreenList(curentScreen: MutableIntState, curentSortField:MutableState<String>) {
        val expanded = remember { mutableStateOf(false) }
        Box(modifier = Modifier.fillMaxSize()) {
            Column(
                modifier = Modifier
                    .fillMaxHeight()
                    .fillMaxWidth()
            ) {
                Row {
                    Box {
                        IconButton(onClick = { expanded.value = true }) {
                            Icon(
                                imageVector = Icons.Default.MoreVert,
                                contentDescription = "Сортировать"
                            )
                        }
                        DropdownMenu(
                            expanded = expanded.value,
                            onDismissRequest = { expanded.value = false }) {
                            DropdownMenuItem(text = { Text(text = "Имя") }, onClick = {
                                curentSortField.value = "name"
                                sqlFunc.GetColection(colectionItems, curentSortField.value)
                                expanded.value = false
                            })
                            DropdownMenuItem(text = { Text(text = "Вес") }, onClick = {
                                curentSortField.value = "weight"
                                sqlFunc.GetColection(colectionItems, curentSortField.value)
                                expanded.value = false
                            })
                            DropdownMenuItem(text = { Text(text = "Рост") }, onClick = {
                                curentSortField.value = "height"
                                sqlFunc.GetColection(colectionItems, curentSortField.value)
                                expanded.value = false
                            })
                            DropdownMenuItem(text = { Text(text = "Возраст") }, onClick = {
                                curentSortField.value = "age"
                                sqlFunc.GetColection(colectionItems, curentSortField.value)
                                expanded.value = false
                            })
                            Divider()
                            DropdownMenuItem(text = { Text(text = "Отмена") }, onClick = {
                                curentSortField.value = "_id"
                                sqlFunc.GetColection(colectionItems, curentSortField.value)
                                expanded.value = false
                            })
                        }
                    }
                    Button(onClick = {
                        curentScreen.intValue = 2
                    }) {
                        Text(text = "Добавить")
                    }
                    Button(onClick = {
                        curentScreen.intValue = 3
                    }) {
                        Text(text = "Удалить")
                    }
                }
                Divider()
                Row(modifier = Modifier.fillMaxWidth()) {
                    Text(text = "Имя", modifier = Modifier.weight(2f))
                    Text(text = "Вес", modifier = Modifier.weight(1f))
                    Text(text = "Рост", modifier = Modifier.weight(1f))
                    Text(text = "Возраст", modifier = Modifier.weight(1f))
                }
                LazyColumn {
                    items(colectionItems) { item ->
                        Row(modifier = Modifier.fillMaxWidth()) {
                            Text(text = item.name, modifier = Modifier.weight(2f), fontSize = 20.sp)
                            Text(
                                text = item.weight.toString(),
                                modifier = Modifier.weight(1f),
                                fontSize = 20.sp
                            )
                            Text(
                                text = item.height.toString(),
                                modifier = Modifier.weight(1f),
                                fontSize = 20.sp
                            )
                            Text(
                                text = item.age.toString(),
                                modifier = Modifier.weight(1f),
                                fontSize = 20.sp
                            )
                        }
                    }
                }
            }
        }
    }
}