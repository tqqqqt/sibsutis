package com.example.tabslab

import androidx.compose.foundation.Image
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.*
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.sp
import androidx.compose.ui.unit.dp
import androidx.compose.ui.res.painterResource

@Composable
fun ImagePage(){
    Column {
        Text(text = "Simple image", fontSize=30.sp)
        Image(painter = painterResource(id = R.drawable.ic_launcher_foreground),contentDescription = "simple picture", modifier = Modifier.size(400.dp).border(1.dp,Color.Black))
    }
}