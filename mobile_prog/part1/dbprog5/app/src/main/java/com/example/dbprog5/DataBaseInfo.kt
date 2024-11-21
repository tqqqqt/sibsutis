package com.example.dbprog5

import android.provider.BaseColumns

object DataBaseInfo {
    const val tableName = "mytable"
    const val name = "name"
    const val weight = "weight"
    const val height = "height"
    const val age = "age"

    const val dataBaseVersion = 1
    const val dataBaseName = "madb.db"

    const val createStr = "CREATE TABLE ${tableName} (${BaseColumns._ID} INTEGER PRIMARY KEY, ${name} TEXT, ${weight} INTEGER, ${height} INTEGER, ${age} INTEGER)"
    const val updateStr = "DROP TABLE IF EXISTS ${tableName}"
}