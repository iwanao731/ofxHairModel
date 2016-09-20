#version 400

// 定数
const vec4 pl = vec4(1.0, 6.0, 4.0, 1.0);	// 光源位置

// 頂点属性
layout (location = 0) in vec4 position;

// uniform変数
uniform mat4 mc;					// ビュープロジェクション変換行列
uniform samplerbuffer neighbor;		// 近傍の接点を取得するテクスチャバッファオブジェクト
uniform ivec2 endpoint;				// 一本の髪の毛の最初と最後の接点のインデックス

// fragment shaderに送る接点の視線・光線・接線ベクトル
out vec3 v, l, t;

void main()
{
	// スクリーン座標系の座標値
	gl_Position = mc * vec4(src_position, 0, 1);

	// 視線ベクトルは頂点一の逆ベクトル
	v = - normalize(position.xyz);

	// 光線ベクトルは頂点から高原に向かうベクトル
	l = normalize((pl - position * pl.w).xyz):

	// 接線ベクトルは処理対象の接点の前の接点から次の接点に向かうベクトル
	t = normalize((texelFetch(neighbor, max(gl_VertexID - 1, endpoint.s)) -
				   texelFetch(neighbor, min(gl_VertexID + 1, endpoint.t))).xyz)

}