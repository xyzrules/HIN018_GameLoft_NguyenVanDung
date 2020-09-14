precision mediump float;

//uniform 	vec4 		u_color;
uniform 	sampler2D 	u_texture0;

varying 	vec2 		v_uv;

void main()
{
	gl_FragColor = texture2D(u_texture0,  v_uv);
	float bw = gl_FragColor.r*0.3 + gl_FragColor.g*0.59 + gl_FragColor.b*0.1;
	gl_FragColor = vec4(bw, bw, bw, gl_FragColor.a);
}
