#pragma once

#include<deque>
#include"../vertex.h"

namespace bear { namespace graphics {

#define VERTEX_SIZE sizeof(Vertex)
#define TRIANGLE_SIZE VERTEX_SIZE * 3
#define QUAD_SIZE VERTEX_SIZE * 6
#define QUAD_MAX_COUNT 500
#define UNLIT_BUFFER_SIZE QUAD_SIZE * QUAD_MAX_COUNT

	/*
	* This renderer batches data into one big buffer (for unlit-primitives)
	* When dealing with rendering textures, we render them after dealing with the unlit-primitives
	* REASON: I don't know how to batch triangle + quads + sprites so this renderer renders sprites seperate from triangle + quads
	*/

	class Shader;
	class Renderable;

	struct unlit_buffers 
	{
		unsigned int VAO, VBO;
	};

	struct texuted_buffers 
	{
		int VAO, VBO, TBO;
		std::deque<Renderable&> m_TextureBatch;
	};

	class BatchRenderer {
	private:
		Shader *m_UnlitShader, *m_TextureShader;
		unlit_buffers _unlit_buffers;
		texuted_buffers _textured_buffers;
		
	public:
		BatchRenderer();
		~BatchRenderer();
	
		/*
		call init or the renderer won't work
		*/
		void init(unsigned int a_Width, unsigned int a_Height);

		/*
		Render routines, use submit between begin&flush
		begin prepares the renderer for new data through submit
		flush renders the submitted data
		*/
		void begin();
		void submit(const Renderable& a_Renderable);
		void flush();

		/*
		shader getters
		*/
		Shader& getUnlitShader();
		Shader& getTextureShader();

	private:
		void submit_unlit(const Renderable& a_UnlitRenderable);
		void submit_texture(const Renderable& a_TexturedRenderable);
	};

} }