#include <Sprite.hlsli>

VS_OUT main(VS_IN In)
{
  VS_OUT vout;
  vout.pos = mul(In.position, In.ndc_transform);
  vout.texcoord = In.texcoord * In.texcoord_transform.zw + In.texcoord_transform.xy;
  vout.color = In.color;

  return vout;
}
