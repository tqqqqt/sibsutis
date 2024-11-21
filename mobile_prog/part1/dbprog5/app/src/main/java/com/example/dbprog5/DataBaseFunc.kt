package com.example.dbprog5

import android.content.ContentValues
import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper

class DataBaseFunc(context: Context) : SQLiteOpenHelper(context, DataBaseInfo.dataBaseName, null, DataBaseInfo.dataBaseVersion) {
    data class DBItem(
        val id: Int,
        val name: String,
        val weight: Int,
        val height: Int,
        val age: Int,
        var deletePoint: Int
    )

    private var myDB:SQLiteDatabase? = null

    override fun onCreate(db: SQLiteDatabase?) {
        //db?.execSQL(DataBaseInfo.createStr)
        myDB?.execSQL(DataBaseInfo.createStr)
    }

    override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
        //db?.execSQL(DataBaseInfo.updateStr)
        //onCreate(db)
        myDB?.execSQL(DataBaseInfo.updateStr)
        onCreate(myDB)
    }

    public fun OpenDataBase(){
        myDB=this.writableDatabase
    }

    public fun CloseDataBase(){
        myDB?.close()
    }

    public fun GetColection(
        colection: MutableList<DBItem>,
        needSort: String
    ) {
        colection.clear()
        val cursor = myDB?.query("mytable", null, null, null, null, null, needSort)
        if (cursor == null) return
        with(cursor) {
            while (this.moveToNext()) {
                val id=cursor.getInt(cursor.getColumnIndexOrThrow("_id"))
                val name = cursor.getString(cursor.getColumnIndexOrThrow("name"))
                val weight = cursor.getInt(cursor.getColumnIndexOrThrow("weight"))
                val height = cursor.getInt(cursor.getColumnIndexOrThrow("height"))
                val age = cursor.getInt(cursor.getColumnIndexOrThrow("age"))
                colection.add(DBItem(id, name, weight, height, age, 0))
            }
        }
        cursor.close()
    }

    public fun AddItem(newName:String, newWeight:Int, newHeight:Int, newAge:Int) {
        val values = ContentValues().apply {
            put("name", newName)
            put("weight", newWeight)
            put("height", newHeight)
            put("age", newAge)
        }
        myDB?.insert("mytable", null, values)
    }

    public fun DelItem(list: MutableList<DBItem>){
        for(i in 0..list.size-1) {
            if(list[i].deletePoint==0) continue
            val str = "DELETE FROM mytable WHERE _id = " + list[i].id.toString()
            myDB?.execSQL(str)
        }
    }
}