package com.example.compase4

import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.size
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.mutableStateOf
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.rotate
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.compase4.ui.theme.Compase4Theme
import kotlin.math.roundToInt

class MainActivity : ComponentActivity(), SensorEventListener {
    private lateinit var manager: SensorManager
    private var degre: MutableState<Float> = mutableStateOf(0f)
    private var magArray = FloatArray(3)
    private var acelArray = FloatArray(3)

    private var rotMatr = FloatArray(9)
    private var orientAngle = FloatArray(3)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        manager = getSystemService(Context.SENSOR_SERVICE) as SensorManager
        setContent {
            Compase4Theme {
                Box(modifier = Modifier
                    .fillMaxSize()
                    .background(Color.White)){
                    MainScreen(degre.value)
                }
            }
        }
    }

    override fun onResume() {
        super.onResume()
        manager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)?.also { acelerom ->
            manager.registerListener(this,acelerom,SensorManager.SENSOR_DELAY_GAME,SensorManager.SENSOR_DELAY_GAME)
        }
        manager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD)?.also{ magField ->
            manager.registerListener(this,magField,SensorManager.SENSOR_DELAY_GAME,SensorManager.SENSOR_DELAY_GAME)
        }
    }

    override fun onPause() {
        super.onPause()
        manager.unregisterListener(this)
    }

    override fun onSensorChanged(event: SensorEvent) {
        if(event.sensor.type == Sensor.TYPE_MAGNETIC_FIELD) System.arraycopy(event.values,0,magArray,0,magArray.size)
        else if(event.sensor.type == Sensor.TYPE_ACCELEROMETER) System.arraycopy(event.values,0,acelArray,0,acelArray.size)
        val azimInRad = this.orientAngle[0]
        val azimInDegr = Math.toDegrees(azimInRad.toDouble()).roundToInt()
        degre.value = if(azimInDegr<0) (azimInDegr+360).toFloat() else azimInDegr.toFloat()
        updateSensorAngle()
    }

    private fun updateSensorAngle(){
        SensorManager.getRotationMatrix(rotMatr,null,acelArray,magArray)
        SensorManager.getOrientation(rotMatr,orientAngle)
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {

    }
}

@Composable
private fun MainScreen(degre: Float){
    Box {
        Image(painter = painterResource(id=R.drawable.kom_num_pad2) , contentDescription = "", modifier = Modifier.size(400.dp).background(Color.Transparent))
        Image(painter = painterResource(id=R.drawable.kom_star), contentDescription = "", modifier = Modifier.size(400.dp).background(Color.Transparent).rotate(-degre))
    }
}