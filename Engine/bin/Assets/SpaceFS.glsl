#version 330 core
//constantes del programa
	uniform sampler2D texturaL;		// tipo sampler2D para texturas 2D
	uniform sampler2D texturaM;		// ‐> unidades de textura (int)
	uniform float BF;				// blending factor
	uniform float intLuzAmb;		// luz ambiente blanca

//valores de entrada
	// in vec4 gl_FragCoord; // predefinida asociada a
				// gl_Position (out del VS)
	// in bool gl_FrontFacing; // predefinida
	in vec2 vUv0; // out del vertex shader
	in vec2 vUv1; // out del vertex shader

//valores de salida
	out vec4 fFragColor; // out del fragment shader

void main() {
	vec3 colorL = vec3(texture(texturaL, vUv0)); // acceso a téxel
	vec3 colorM = vec3(texture(texturaM, vUv1)); // configuración!
	vec3 color = colorL * colorM;
	//intLuzAmb =  mix ‐> (1‐BF).colorL + BF.colorM;
	fFragColor = vec4(color, 1.0); // out
}