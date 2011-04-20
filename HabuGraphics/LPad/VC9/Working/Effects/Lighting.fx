//=============================================================================
// PhongDirLtTex.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Phong directional light & texture.
//=============================================================================

struct Material
{
	float4 ambient;
	float4 diffuse;
	float4 spec;
	float  specPower;
};

struct DirLight
{
	float4 ambient;
	float4 diffuse;
	float4 spec;
    float3 DirW; 
};

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInvTrans;
uniform extern float4x4 gWVP;
uniform extern Material gMaterial;
uniform extern DirLight gLight;
uniform extern float3   gEyePosW;
uniform extern texture  gTexture;

sampler TexS = sampler_state
{
	Texture = <gTexture>;
	MinFilter = Anisotropic;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 4;
	AddressU  = WRAP;
    AddressV  = WRAP;
};
 
struct OutputVS
{
    float4 posH    : POSITION0;
    float3 normalW : TEXCOORD0;
    float3 toEyeW  : TEXCOORD1;
    float2 tex0    : TEXCOORD2;
};

OutputVS PhongLightingVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0: TEXCOORD0)
{
  // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Transform normal to world space.
	outVS.normalW = mul(float4(normalL, 0.0f), gWorldInvTrans).xyz;
	
	// Transform vertex position to world space.
	float3 posW  = mul(float4(posL, 1.0f), gWorld).xyz;
	
	// Compute the unit vector from the vertex to the eye.
	outVS.toEyeW = gEyePosW - posW;
	
	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	
	// Pass on texture coordinates to be interpolated in rasterization.
	outVS.tex0 = tex0;

	// Done--return the output.
  return outVS;
}

float4 PhongLightingPS(float3 normalW : TEXCOORD0, float3 toEyeW  : TEXCOORD1, float2 tex0 : TEXCOORD2) : COLOR
{
	// Interpolated normals can become unnormal--so normalize.
	normalW = normalize(normalW);
	toEyeW  = normalize(toEyeW);
	
	// Light vector is opposite the direction of the light.
	float3 lightVecW = -gLight.DirW;
	
	// Compute the reflection vector.
	float3 r = reflect(-lightVecW, normalW);
	
	// Determine how much (if any) specular light makes it into the eye.
	float t = pow(abs(max(dot(r, toEyeW), 0.0f)), gMaterial.specPower);
	
	// Determine the diffuse light intensity that strikes the vertex.
	float s = max(dot(lightVecW, normalW), 0.0f);
	
	// Compute the ambient, diffuse and specular terms separatly. 
	float3 spec = t*(gMaterial.spec*gLight.spec).rgb;
	float3 diffuse = s*(gMaterial.diffuse*gLight.diffuse).rgb;
	float3 ambient = gMaterial.ambient*gLight.ambient;
	
	// Get the texture color.
	float4 texColor = tex2D(TexS, tex0);
	
	// Combine the color from lighting with the texture color.
	float3 color = (ambient + diffuse)*texColor.rgb + spec;
		
	// Sum all the terms together and copy over the diffuse alpha.
   return float4(color, gMaterial.diffuse.a*texColor.a);
}

technique LightingTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 PhongLightingVS();
        pixelShader  = compile ps_2_0 PhongLightingPS();
    }
}