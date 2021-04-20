#version 330 core//
#ifdef GL_ES
	precision mediump float;
#endif
//atributos de entrada
	in vec4 vertex;				//	atributos de los vértices a procesar(coordenadas de posicion)
	in vec2 uv0;				//	coordenadas de textura 0

// constantes de programa
	uniform mat4 modelViewProjMat; 
	uniform float FZ;
	uniform float  SinTiempo;
	//uniform mat4 viewMatrix;
	//uniform mat4 projMatrix;
	//uniform mat3 normalMatrix;
	//uniform mat2 texCoordMatrix;

//Atributos de salida (out del vertex shader) hay que darles un valor
	out vec2 vUv0; //coordenadas de textura 0
	out vec2 vUv1;
	// out vec4 gl_Position; // predefinida obligatoria

void main() {
    vUv0 = uv0;	//	se pasan las coordenadas de textura
	vec2 coor0 = uv0 ;//+ aux;
	//coor0 = coor0 / 1.5;
	//	Valores entre 0.0 -> 1.0 para pasar del intervalor [-1 , 1] a [0.5 , 1.0]
    float aux = (SinTiempo * 0.25) + 0.75;
	vec2 coor1 = (coor0 -0.5) * (aux) + 0.5;
	vUv1 = coor1;
    gl_Position = modelViewProjMat * vertex;	//	obligatorio
}
// (Clipping coordinates)