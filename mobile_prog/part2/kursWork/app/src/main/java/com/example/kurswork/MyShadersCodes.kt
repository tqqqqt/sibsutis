package com.example.kurswork

class MyShadersCodes {
    var vertex_shader=
            "attribute vec3 a_vertex;" +
            "attribute vec3 a_normal;" +
            "uniform mat4 u_modelViewProjectionMatrix;" +
            "varying vec3 v_vertex;" +
            "varying vec3 v_normal;" +
            "void main(){" +
            "v_vertex=a_vertex;" +
            "vec3 n_normal=normalize(a_normal);" +
            "v_normal=n_normal;" +
            "gl_Position=u_modelViewProjectionMatrix * vec4(a_vertex,1.0);" +
            "}"

    var vertex_sphere_shader=
                "attribute vec3 a_vertex;" +
                "attribute vec3 a_normal;" +
                "uniform mat4 u_modelViewProjectionMatrix;" +
                "varying vec3 v_vertex;" +
                "varying vec3 v_normal;" +
                "varying vec2 v_texcoord;" +
                "void main(){" +
                "v_vertex=a_vertex;" +
                "vec3 n_normal=normalize(a_normal);" +
                "v_normal=n_normal;" +
                "v_texcoord.s=a_vertex.x;" +
                "v_texcoord.t=a_vertex.y;" +
                "gl_Position=u_modelViewProjectionMatrix * vec4(a_vertex,1.0);" +
                "}"

    var fragment_tex_shader_light="precision highp float;"+
            "uniform vec3 u_camera;"+
            "uniform vec3 u_lightPosition;"+
            "varying vec3 v_vertex;"+
            "varying vec3 v_normal;" +
            "varying vec2 v_texcoord;" +
            "uniform sampler2D u_texture;"+
            "void main() {"+
            "vec3 n_normal=normalize(v_normal);"+
            "vec3 lightvector = normalize(u_lightPosition - v_vertex);"+
            "vec3 lookvector = normalize(u_camera - v_vertex);"+
            "float ambient=0.02;"+ //0.001//0.1
            "float k_diffuse=0.51;"+ //0.36//0.7
            "float k_specular=0.3;"+ //0.6//0.3
            "float diffuse = k_diffuse * max(dot(n_normal, lightvector), 0.0);"+
            "vec3 reflectvector = reflect(-lightvector, n_normal);"+
            "float specular=k_specular*pow( max(dot(lookvector,reflectvector),0.0),40.0);"+
            "vec4 one=vec4(1.0,1.0,1.0,1.0);"+
            "vec4 lightColor=(ambient+diffuse+specular)*one;" +
            "vec4 textureColor=texture2D(u_texture,v_texcoord);"+
            "gl_FragColor=lightColor*textureColor; "+
            "}"

    var fragment_shader_light= "precision mediump float;"+
                "uniform vec3 u_camera;"+
                "uniform vec3 u_lightPosition;"+
                "varying vec3 v_vertex;"+
                "varying vec3 v_normal;"+
                "void main() {"+
                "vec3 n_normal=normalize(v_normal);"+
                "vec3 lightvector = normalize(u_lightPosition - v_vertex);"+
                "vec3 lookvector = normalize(u_camera - v_vertex);"+
                "float ambient=0.001;"+
                "float k_diffuse=0.36;"+
                "float k_specular=0.3;"+
                "float diffuse = k_diffuse * max(dot(n_normal, lightvector), 0.0);"+
                "vec3 reflectvector = reflect(-lightvector, n_normal);"+
                "float specular=k_specular*pow( max(dot(lookvector,reflectvector),0.0),40.0);"+
                "vec4 one=vec4(1.0,1.0,1.0,1.0);"+
                "vec4 lightColor=(ambient+diffuse+specular)*one;"+
                "gl_FragColor=lightColor;"+
                "}"

    var vertex_shader_cup="attribute vec3 a_vertex;" +
            "uniform mat4 u_modelViewProjectionMatrix;" +
            "void main(){" +
            "gl_Position=u_modelViewProjectionMatrix * vec4(a_vertex,1.0);" +
            "}"

    var fragment_custom_color="precision mediump float;" +
            "uniform vec4 u_color;" +
            "void main(){" +
            "gl_FragColor=u_color;" +
            "}"
}