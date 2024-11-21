package com.example.astronomicalhandbook

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Canvas
import android.graphics.Paint
import android.opengl.GLES10
import android.opengl.GLSurfaceView
import android.opengl.GLU
import android.opengl.GLUtils
import android.util.Log
import java.nio.FloatBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGlRender: GLSurfaceView.Renderer {
    private var context:Context
    private var my_cube:Cube
    private var my_square:Square
    private lateinit var my_sphere:Array<Sphere>
    private var left_arrow: MyButtons
    private var right_arrow: MyButtons
    private var button_info: MyButtons
    private var texture_names: Array<Int>
    private var textures: IntArray
    private var p:Float
    private var angle:Float
    private var curent_planet: Int
    private var apply_planet: Int
    private var curent_screen: Int
    private var curent_rotate: Int
    private lateinit var textes: IntArray
    private var my_cube_2:Cube
    private var my_water_ground: WaterGround
    
    constructor(context: Context){
        this.context=context
        my_cube=Cube(context,1)
        my_square=Square()
        left_arrow=MyButtons(1)
        right_arrow=MyButtons(2)
        button_info= MyButtons(3)
        my_cube_2=Cube(context,2)
        my_water_ground=WaterGround(context,10,10)
        p=0f
        curent_planet=1
        apply_planet=-1
        curent_screen=1
        curent_rotate=1
        angle=0f
        texture_names= arrayOf(R.drawable.sun,R.drawable.mercy,R.drawable.venera,R.drawable.earth,R.drawable.moon,R.drawable.marse,
            R.drawable.upiter,R.drawable.saturn,R.drawable.uran,R.drawable.neptun)
        textures= IntArray(texture_names.size)
    }

    override fun onSurfaceCreated(gl: GL10?, p1: EGLConfig?) {
        gl!!.glClearColor(0.0f,0.0f,0.0f,0.0f)
        gl.glClearDepthf(1f)
        my_sphere=arrayOf(
            Sphere(4f), Sphere(1f), Sphere(1f), Sphere(1f), Sphere(0.5f), Sphere(1f),
            Sphere(2f), Sphere(2f), Sphere(1.4f), Sphere(1.4f)
        )

        gl.glGenTextures(10,textures,0)
        for(i in 0..<texture_names.size){
            gl.glBindTexture(GL10.GL_TEXTURE_2D,textures[i])
            gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_MIN_FILTER,GL10.GL_LINEAR.toFloat())
            val str=context.resources.openRawResource(texture_names[i])
            val bitmap=BitmapFactory.decodeStream(str)
            GLUtils.texImage2D(GL10.GL_TEXTURE_2D,0,bitmap,0)
            bitmap.recycle()
        }

        var textt=PlanetText()
        textes=IntArray(textt.text_mas.size)
        gl.glGenTextures(10,textes,0)
        for(i in 0..<textes.size){
            val bitmap = Bitmap.createBitmap(1024, 1024, Bitmap.Config.ARGB_4444)
            val canvas = Canvas(bitmap)
            bitmap.eraseColor(0)
            var background = context.getResources().getDrawable(R.drawable.bg)
            background.setBounds(0, 0, 1024, 1024)
            background.draw(canvas)
            var textPaint = Paint()
            textPaint.setTextSize(16f)
            textPaint.setAntiAlias(true)
            textPaint.setARGB(0xff, 0x00, 0x00, 0x00)
            for( j in 0..<textt.text_mas[i].size) canvas.drawText(textt.text_mas[i][j],260f,(300+(20*j)).toFloat(), textPaint)
            gl.glBindTexture(GL10.GL_TEXTURE_2D, textes[i])
            gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_NEAREST.toFloat())
            gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR.toFloat())
            GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);
            bitmap.recycle();
        }
    }

    override fun onSurfaceChanged(gl: GL10?, screen_width: Int, screen_height: Int) {
        gl!!.glViewport(0,0,screen_width,screen_height)
        GLES10.glMatrixMode(GLES10.GL_PROJECTION)
        GLES10.glLoadIdentity()
        if(screen_height>screen_width){
            GLES10.glOrthof(/*x cord*/-10.0f, 10.0f,/*y cord*/ -20.0f, 20.0f,/*z cord*/ -40.0f, 40.0f)
            curent_rotate=1
        }
        else{
            GLES10.glOrthof(/*x cord*/ -20.0f, 20.0f,/*y cord*/ -10.0f, 10.0f,/*z cord*/ -40.0f, 40.0f)
            curent_rotate=2
        }
        GLES10.glMatrixMode(GLES10.GL_MODELVIEW)
        gl.glLoadIdentity()
    }

    override fun onDrawFrame(gl: GL10?) {
        if(curent_screen==1) {
            if (p == 360f) p = 0f
            else p += 2f
            if (angle == 360f) angle = 0f
            else angle += 0.15f

            gl!!.glClear(GL10.GL_COLOR_BUFFER_BIT or GL10.GL_DEPTH_BUFFER_BIT)
            gl.glClear(GL10.GL_TEXTURE_2D)

            /* background */
            my_cube.draw(gl,0)

            gl.glEnable(GL10.GL_TEXTURE_2D)
            gl.glEnable(GL10.GL_DEPTH_TEST)
            gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY)

            /* spheres and square */
            var xx = 0f
            var zz = 0f
            for (i in 0..<my_sphere.size) {
                gl.glPushMatrix()
                if (i == 1) gl.glTranslatef(
                    (5 * Math.cos((angle * 0.2f).toDouble())).toFloat(), 0f, (5 * Math.sin((angle * 0.2f).toDouble())).toFloat())
                else if (i == 2) gl.glTranslatef(
                    (8 * Math.cos((angle * 0.17f).toDouble())).toFloat(), 0f, (8 * Math.sin((angle * 0.17f).toDouble())).toFloat())
                else if (i == 3) {
                    xx = (11 * (Math.cos((angle * 0.15f).toDouble()))).toFloat()
                    zz = (11 * (Math.sin((angle * 0.15f).toDouble()))).toFloat()
                    gl.glTranslatef(xx, 0f, zz)
                } else if (i == 4) gl.glTranslatef(
                    xx + (3 * Math.cos((angle * 0.17f).toDouble())).toFloat(), 0f, zz + (2 * Math.sin((angle * 0.17f).toDouble())).toFloat())
                else if (i == 5) gl.glTranslatef(
                    (14 * Math.cos((angle * 0.12f).toDouble())).toFloat(), 0f, 0 + (14 * Math.sin((angle * 0.12f).toDouble())).toFloat())
                else if (i == 6) gl.glTranslatef(
                    (17 * Math.cos((angle * 0.1f).toDouble())).toFloat(), 0f, (17 * Math.sin((angle * 0.1f).toDouble())).toFloat())
                else if (i == 7) gl.glTranslatef(
                    (20 * Math.cos((angle * 0.08f).toDouble())).toFloat(), 0f, (20 * Math.sin((angle * 0.08f).toDouble())).toFloat())
                else if (i == 8) gl.glTranslatef(
                    (23 * Math.cos((angle * 0.05f).toDouble())).toFloat(), 0f, (23 * Math.sin((angle * 0.05f).toDouble())).toFloat())
                else if (i == 9) gl.glTranslatef(
                    (26 * Math.cos((angle * 0.02f).toDouble())).toFloat(), 0f, (26 * Math.sin((angle * 0.02f).toDouble())).toFloat())
                gl.glBindTexture(GL10.GL_TEXTURE_2D, textures[i])
                gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, my_sphere[i].textureBuffer)
                gl.glPushMatrix()
                gl.glRotatef(90f, 1f, 0f, 0f)
                gl.glRotatef(p, 0f, 0f, 1f)
                my_sphere[i].draw(gl)
                gl.glPopMatrix()
                if (i == curent_planet) {
                    if (curent_planet != apply_planet) {
                        my_square.changeVertex(my_sphere[curent_planet].getRadius())
                        apply_planet = curent_planet
                    }
                    my_square.draw(gl)
                }
                gl.glPopMatrix()
            }

            gl.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY)
            gl.glDisable(GL10.GL_DEPTH_TEST)
            gl.glDisable(GL10.GL_TEXTURE_2D)

            /* buttons */
            /* arrows */
            gl.glPushMatrix()
            if(curent_rotate==1) gl.glTranslatef(-5f, -15f, 0f)
            else if(curent_rotate==2) gl.glTranslatef(-15f, -7f, 0f)
            left_arrow.draw(gl)
            gl.glPopMatrix()

            gl.glPushMatrix()
            if(curent_rotate==1) gl.glTranslatef(-3f, -15f, 0f)
            else if(curent_rotate==2) gl.glTranslatef(-13f, -7f, 0f)
            right_arrow.draw(gl)
            gl.glPopMatrix()

            gl.glPushMatrix()
            if(curent_rotate==1) gl.glTranslatef(5f, -14f, 0f)
            else if(curent_rotate==2) gl.glTranslatef(15f, -6f, 0f)
            button_info.draw(gl)
            gl.glPopMatrix()
        }
        else if(curent_screen==2){
            if (p == 360f) p = 0f
            else p += 2f

            gl!!.glClear(GL10.GL_COLOR_BUFFER_BIT or GL10.GL_DEPTH_BUFFER_BIT)
            gl.glClear(GL10.GL_TEXTURE_2D)

            gl.glEnable(GL10.GL_TEXTURE_2D)
            gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY)

            /* text */
            gl.glBindTexture(GL10.GL_TEXTURE_2D, textes[curent_planet])
            gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, my_cube_2.texture_buffer)
            my_cube_2.draw(gl,1)

            gl.glEnable(GL10.GL_DEPTH_TEST)

            /* planeta */
            if(curent_planet==4){
                gl.glDisable(GL10.GL_DEPTH_TEST)
                var light_amb=FloatBuffer.wrap(arrayOf(0.2f,0.2f,0.2f,1f).toFloatArray())
                var light_dif=FloatBuffer.wrap(arrayOf(1f,1f,1f,1f).toFloatArray())
                var light_spe=FloatBuffer.wrap(arrayOf(1f,1f,1f,1f).toFloatArray())
                var light_pos=FloatBuffer.wrap(arrayOf(0f,0f,1f,1f).toFloatArray())

                gl.glEnable(GL10.GL_DEPTH_TEST)
                gl.glEnable(GL10.GL_LIGHTING)
                gl.glEnable(GL10.GL_LIGHT0)
                gl.glEnable(GL10.GL_COLOR_MATERIAL)
                gl.glEnable(GL10.GL_NORMALIZE)

                gl.glLightfv(GL10.GL_LIGHT0,GL10.GL_AMBIENT,light_amb)
                gl.glLightfv(GL10.GL_LIGHT0,GL10.GL_DIFFUSE,light_dif)
                gl.glLightfv(GL10.GL_LIGHT0,GL10.GL_SPECULAR,light_spe)
                gl.glPushMatrix()
                gl.glTranslatef(18f,16f,10f)
                gl.glLightfv(GL10.GL_LIGHT0,GL10.GL_POSITION,light_pos)
                gl.glPopMatrix()

                var material_dif=FloatBuffer.wrap(arrayOf(0.2f,0.2f,0.2f,1f).toFloatArray())
                var material_amb=FloatBuffer.wrap(arrayOf(1f,1f,1f,1f).toFloatArray())
                var material_spec=FloatBuffer.wrap(arrayOf(1f,1f,1f,1f).toFloatArray())
                gl.glMaterialfv(GL10.GL_FRONT_AND_BACK,GL10.GL_AMBIENT,material_amb)
                gl.glMaterialfv(GL10.GL_FRONT_AND_BACK,GL10.GL_DIFFUSE,material_dif)
                gl.glMaterialfv(GL10.GL_FRONT_AND_BACK,GL10.GL_SPECULAR,material_spec)
                gl.glMaterialf(GL10.GL_FRONT,GL10.GL_SHININESS,64f)
            }

            gl.glBindTexture(GL10.GL_TEXTURE_2D, textures[curent_planet])
            gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, my_sphere[curent_planet].textureBuffer)
            gl.glPushMatrix()
            if(curent_rotate==1) gl.glTranslatef(0f,15f,6f)
            else if(curent_rotate==2) gl.glTranslatef(-15f,5f,6f)
            if(curent_planet==1 || curent_planet==2 || curent_planet==3 ||curent_planet==5
                || curent_planet==8 || curent_planet==9) gl.glScalef(3f,3f,3f)
            else if(curent_planet==6 || curent_planet==7) gl.glScalef(2f,2f,2f)
            else if(curent_planet==4) gl.glScalef(5f,5f,5f)
            gl.glRotatef(90f, 1f, 0f, 0f)
            gl.glRotatef(p, 0f, 0f, 1f)
            my_sphere[curent_planet].draw(gl)
            gl.glPopMatrix()

            if(curent_planet==9){
                gl.glPushMatrix()
                gl.glTranslatef(-3f,-10f,6f)
                my_water_ground.draw(gl)
                gl.glPopMatrix()
            }

            gl.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY)
            gl.glDisable(GL10.GL_TEXTURE_2D)

            /* button */
            gl.glPushMatrix()
            if(curent_rotate==1) gl.glTranslatef(5f, -14f, 6f)
            else if(curent_rotate==2) gl.glTranslatef(15f, -6f, 6f)
            button_info.draw(gl)
            gl.glPopMatrix()

            if(curent_planet==4){
                gl.glDisable(GL10.GL_LIGHTING)
                gl.glDisable(GL10.GL_COLOR_MATERIAL)
                gl.glDisable(GL10.GL_NORMALIZE)
            }
            gl.glDisable(GL10.GL_DEPTH_TEST)
        }
    }

    fun clickScreen(click_x: Float, click_y: Float){
        if(curent_screen==1) {
            if(curent_rotate==1) {
                if ((click_x >= 0.05f && click_x <= 0.25f) && (click_y >= 0.8f && click_y <= 0.9f)) {
                    curent_planet--
                    if (curent_planet < 0) curent_planet = 9
                }
                else if ((click_x >= 0.34f && click_x <= 0.55f) && (click_y >= 0.8f && click_y <= 0.9f)) {
                    curent_planet++
                    if (curent_planet > 9) curent_planet = 0
                }
                else if ((click_x >= 0.68f && click_x <= 0.87f) && (click_y >= 0.8f && click_y <= 0.9f)) curent_screen = 2
            }
            else if(curent_rotate==2){
                if ((click_x >= 0.01f && click_x <= 0.12f) && (click_y >= 0.69f && click_y <= 0.9f)) {
                    curent_planet--
                    if (curent_planet < 0) curent_planet = 9
                }
                else if ((click_x >= 0.17f && click_x <= 0.29f) && (click_y >= 0.69f && click_y <= 0.9f)) {
                    curent_planet++
                    if (curent_planet > 9) curent_planet = 0
                }
                else if ((click_x >= 0.83f && click_x <= 0.93f) && (click_y >= 0.69f && click_y <= 0.9f)) curent_screen = 2
            }
        }
        else if(curent_screen==2){
            if (curent_rotate==1 && (click_x >= 0.68f && click_x <= 0.87f) && (click_y >= 0.8f && click_y <= 0.9f)) curent_screen = 1
            else if (curent_rotate==2 && (click_x >= 0.83f && click_x <= 0.93f) && (click_y >= 0.7f && click_y <= 0.91f)) curent_screen = 1
        }
    }
}

class PlanetText{
    var text_mas: Array<Array<String>>

    init{
        text_mas= arrayOf(
            arrayOf("Солнце","Со́лнце — одна из звёзд нашей Галактики (Млечный Путь).","Единственная звезда Солнечной системы.","Вокруг Солнца обращаются другие объекты этой системы.", "По спектральной классификации Солнце относится к типу G2V.","Средняя плотность Солнца составляет 1,4 г/см³.","Эффективная температура поверхности Солнца — 5780 кельвин."),
            arrayOf("Меркурий","Мерку́рий — наименьшая планета Солнечной системы и самая","близкая к Солнцу", "Быстрее всех движется вокруг солнца.","Ось Меркурия имеет наименьший наклон из всех планет","Солнечной системы.","Температура его поверхности меняется сильнее, чем на любой","другой планете Солнечной системы."),
            arrayOf("Венера","Вене́ра — вторая по удалённости от Солнца и шестая по размеру","планета Солнечной системы.","Названа в честь древнеримской богини любви Венеры.","По ряду характеристик — например, по массе и размерам — ","Венера считается «сестрой» Земли.","Венера не имеет естественных спутников","Венера имеет плотную атмосферу, состоящую более чем на 96 %","из углекислого газа."),
            arrayOf("Земля","Земля́ — третья по удалённости от Солнца планета Солнечной","системы.","Самая плотная, пятая по диаметру и массе среди всех планет","Солнечной системы.","Единственное известное человеку в настоящее время тело во","Вселенной, населённое живыми организмами."," Жизнь, предположительно, появилась на Земле примерно 4,25","млрд лет назад."),
            arrayOf("Луна","Луна́ — единственный естественный спутник Земли.","Самый близкий к Солнцу спутник планеты.","Луна появилась около 4,5 млрд лет назад, немного позже Земли","На сегодняшний день Луна является единственным внеземным","астрономическим объектом, на котором побывал человек."),
            arrayOf("Марсе","Марс — четвёртая по удалённости от Солнца и седьмая по размеру","планета Солнечной системы.","Наряду с Меркурием, Венерой и Землёй принадлежит к семейству","планет земной группы.","Из-за красноватого оттенка поверхности, придаваемого ей","минералом маггемитом — γ-оксидом железа(III), Марс называют","Красной планетой.","Атмосфера Марса сильно разрежена."),
            arrayOf("Юпитер","Юпи́тер — крупнейшая планета Солнечной системы, пятая по","удалённости от Солнца.","Наряду с Сатурном Юпитер классифицируется как газовый гигант.","Планета была известна людям с глубокой древности, что нашло","своё отражение в мифологии и религиозных верованиях","различных культур.","Ряд атмосферных явлений на Юпитере имеет масштабы, на","порядки превосходящие земные."),
            arrayOf("Сатурн","Сату́рн — шестая планета по удалённости от Солнца и вторая по","размерам планета в Солнечной системе после Юпитера.","Сатурн классифицируется как газовая планета-гигант.","Сатурн назван в честь римского бога земледелия.","В основном Сатурн состоит из водорода, с примесями гелия и","следами воды, метана, аммиака и тяжёлых элементов."),
            arrayOf("Уран","Ура́н — планета Солнечной системы, седьмая по удалённости от"," Солнца, третья по диаметру и четвёртая по массе.","Названа в честь греческого бога неба Урана.","Уран стал первой планетой, обнаруженной в Новое время и при","помощи телескопа.","В недрах Урана и схожего с ним Нептуна отсутствует","металлический водород, но зато много льда в его","высокотемпературных модификациях."),
            arrayOf("Нептун","Непту́н — восьмая и самая дальняя от Солнца планета Солнечной"," системы.","Его масса превышает массу Земли в 17,2 раза и является третьей","среди планет Солнечной системы.","Обнаружен 23 сентября 1846 года.","Обнаружение непредсказуемых изменений орбиты Урана","породило гипотезу о неизвестной планете, гравитационным","возмущающим влиянием которой они и обусловлены.","Нептун по составу близок к Урану"))
    }
}