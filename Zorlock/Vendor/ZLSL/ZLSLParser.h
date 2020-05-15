#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sstream>
#include "lexertk.hpp"


namespace Zorlock
{



	class ZLSLParser
	{
	public:

		enum ShaderSyntax
		{
			SYNTAX_NONE,
			RADIANS,
			DEGREES,
			SIN,
			COS,
			TAN,
			ASIN,
			ACOS,
			ATAN,
			POW,
			EXP,
			MIN,
			LOG,
			SQRT,
			RSQRT,
			ABS,
			SIGN,
			FLOOR,
			CEIL,
			FRACT,
			MOD,
			MAX,
			CLAMP,
			MIX,
			STEP,
			SMSTEP,
			LENGTH,
			DIST,
			DOT,
			CROSS,
			NORMALIZE,
			FFOWARD,
			REFLECT,
			REFRACT,
			LESSTHAN,
			LESSTHANEQ,
			GREATERTHAN,
			GREATERTHANEQ,
			EQUAL,
			NOTEQUAL,
			ANY,
			ALL,
			NOT
			
		};

		enum FunctionNames
		{
			NO_MAIN,
			MAIN
		};

		enum OutPutShaderType
		{
			GLSL,
			HLSL
		};

		enum ShaderSection
		{
			VERTEXSHADER,
			FRAGMENTSHADER
		};

		enum VarCommandValue {
			COM_NONE,
			Uniform,
			Varying,
			Attribute,
			Out,
			In,
			Type,
			Version,
			Constant,
			Layout,
			Function,
			Texture,
			Int,
			Z_Position,
			Z_PointSize,
			Z_FragColor,
			Z_FragData,
			Z_FragCoord,
			Z_FrontFacing,
			Z_PointCoord,
			Z_FragDepth,
			Z_Return,
			Z_NA
			

		};

		enum VariableTypes {
			VAR_NONE,
			FLOAT,
			INT,
			BOOL,
			VEC2,
			VEC3,
			VEC4,
			BVEC2,
			BVEC3,
			BVEC4,
			IVEC2,
			IVEC3,
			IVEC4,
			MAT2,
			MAT3,
			MAT4,
			SAMPLER2D,
			SAMPLERCUBE,
			VARVOID,
			VARVERTEX,
			PIXEL,
			CORE
			
		};

		enum SemanticTypes
		{
			SEM_NONE,
			POSITION,
			COLOR,
			TEXCOORD,
			NORMAL,
			BINORMAL,
			BLENDWEIGHT,
			BLENDINDICES,
			POSITIONT,
			TANGENT,
			FOG,
			VFACE
			
		};

		class ZLSLDeclaredVariables
		{
		public:
			VarCommandValue command;
			VariableTypes vartype;
			std::string varname;
			std::string arithmetic;
			uint32_t index;
			bool isArray;
			bool issemantic;
			size_t count;
			SemanticTypes semantic;
			VarCommandValue inout;
			std::vector<std::string> val_list;
		};


		class ZLSLSyntax
		{
		public:
			std::string variable;
			VarCommandValue command;
			VariableTypes vartype;
			std::string varname;
			ShaderSyntax syntax;
			std::string original;
			std::vector<ZLSLDeclaredVariables> functionArgVarList;
			size_t begin;
			size_t end;
		};

		class ZLSLFunctions
		{
		public:
			VariableTypes returnType;
			std::string functionName;
			std::vector<ZLSLDeclaredVariables> functionArgVarList;
			//temporary
			std::string functionBody;
			std::vector<ZLSLSyntax> functionBodySyntax;
		};




		struct variable_decl_definition
		{
			variable_decl_definition() : command(""), varname(""), vartype(""), index(""), isarray(false), value(""), semantic(""), inout("")
			{

			}

			std::string command;
			std::string varname;
			std::string vartype;
			std::string index;
			std::string value;
			std::string semantic;
			std::string inout;
			bool isarray;
			std::vector<std::string> arrayvals;
			void clear()
			{
				command.clear();
				varname.clear();
				vartype.clear();
				index.clear();
				value.clear();
				semantic.clear();
				inout.clear();
				arrayvals.clear();
				isarray = false;
			}
		};


		struct syntax_definition
		{

			std::string funcname;
			std::string syntax;
			std::string command;
			std::string varname;
			std::string vartype;
			std::string value;
			std::string begin;
			std::string end;
			std::string original;
			std::vector<ZLSLDeclaredVariables> var_list;
			void clear()
			{
				funcname.clear();
				command.clear();
				varname.clear();
				vartype.clear();
				value.clear();
				syntax.clear();
				begin.clear();
				end.clear();
				original.clear();
				var_list.clear();
			}

		};

		struct function_definition
		{


			std::string returntype;
			std::string name;
			std::string body;
			std::vector<ZLSLDeclaredVariables> var_list;

			void clear()
			{
				returntype.clear();
				name.clear();
				body.clear();
				var_list.clear();


			}
		};

		struct functionbodyfunc_definition
		{
			std::string name;
			std::vector<ZLSLDeclaredVariables> arguments;

			void clear()
			{
				arguments.clear();
				name.clear();
			}
		};

		struct parse_functionbodyfunc_definition_impl : public lexertk::parser_helper
		{
		public:
			ZLSLParser* parser;

			bool process(std::string& func_def, functionbodyfunc_definition& fd);
		};

		struct parse_function_definition_impl : public lexertk::parser_helper
		{
		public:
			ZLSLParser* parser;

			bool process(std::string& func_def, function_definition& fd);

		};

		struct parse_variable_decl_definition_impl : public lexertk::parser_helper
		{
		public:
			ZLSLParser* parser;

			bool process(std::string& var_def, variable_decl_definition& fd);

		};


		struct parse_funcbody_decl_definition_impl : public lexertk::parser_helper
		{
		public:
			ZLSLParser* parser;

			bool process(std::string& var_def, syntax_definition& fd);
			bool ParseToken(syntax_definition& fd);
		};

		bool parse_functionbody_definition(std::string& func_def, syntax_definition& fd);
		std::string Parsefunctionbodiess(std::string residual, syntax_definition& fd);
		bool parse_function_definition(std::string& func_def, function_definition& fd);
		std::string Parsefunctions(std::string residual, function_definition& fd);
		bool parse_variable_decl_definition(std::string& var_def, variable_decl_definition& fd);
		std::string ParsevariableDeclares(std::string residual, variable_decl_definition& vd, function_definition& fd, syntax_definition& fbd);
		std::string ReturnGLSLDeclares(std::vector<ZLSLDeclaredVariables> dec);
		std::string ReturnHLSLDeclares(std::vector<ZLSLDeclaredVariables> dec);
		std::string ReturnGLSLFunctions(std::vector<ZLSLFunctions> funcs, bool isvert);
		std::string ReturnHLSLFunctions(std::vector<ZLSLFunctions> funcs, bool isvert);
		std::string ReturnGLSLFunctionBody(ZLSLFunctions func, bool isvert);
		std::string ReturnHLSLFunctionBody(ZLSLFunctions func, bool isvert);
		std::string IsDeclaredVar(std::string& varname);
		std::string GetDeclareType(std::string& varname);
		uint32_t GetSamplerIndex(std::string varname);
		void MapFunctions();
		void MapVariables();
		void MapGLSLVariables();
		void MapHLSLVariables();
		void MapSyntax();
	public:

		ZLSLParser();
		~ZLSLParser();
	private:
		variable_decl_definition vd;
		function_definition fd;
		syntax_definition fbd;
		functionbodyfunc_definition fbf;
		parse_variable_decl_definition_impl vparser;
		parse_function_definition_impl fparser;
		parse_funcbody_decl_definition_impl fbodyparser;
		parse_functionbodyfunc_definition_impl fbodyfuncparser;

		bool isVertex;
	public:
		bool Parse(std::string filename);
		bool ParseString(std::string shader);
		functionbodyfunc_definition& ParseFunctionBody(std::string func);
		std::string GetShader(OutPutShaderType output, ShaderSection section);
		void SaveShader(std::string shaderdata, std::string shaderfile);
		

		std::vector<ZLSLDeclaredVariables> vertexVars;
		std::vector<ZLSLDeclaredVariables> vertexUniforms;
		std::vector<ZLSLDeclaredVariables> vlayoutVars;
		std::vector<ZLSLDeclaredVariables> voutVars;

		std::vector<ZLSLDeclaredVariables> pixelVars;
		std::vector<ZLSLDeclaredVariables> pixelUniforms;
		std::vector<ZLSLDeclaredVariables> playoutVars;
		std::vector<ZLSLDeclaredVariables> pinVars;
		
		
		
		std::vector<ZLSLFunctions> vertexFunctions;
		std::vector<ZLSLFunctions> pixelFunctions;

	

		std::map<std::string, VarCommandValue> s_mapStringCommands;
		std::map<std::string, VariableTypes> s_mapStringVariables;
		std::map<std::string, SemanticTypes> s_mapStringSemantics;
		std::map<std::string, FunctionNames> s_mapFunctionNames;
		std::map<std::string, ShaderSyntax> s_mapSyntaxNames;


		std::map<VariableTypes,std::string> s_mapGLSLVariables;
		std::map<VariableTypes, std::string> s_mapHLSLVariables;

		std::map<VarCommandValue, std::string> s_mapGLSLCommands;
		std::map<VarCommandValue, std::string> s_mapHLSLCommands;

		std::map<SemanticTypes, std::string> s_mapGLSLLayouts;
		std::map<SemanticTypes, std::string> s_mapHLSLLayouts;

		std::map<FunctionNames, std::string> s_mapNameFunctions;

		static void ReplaceAll(std::string& str, const std::string from, const std::string to)
		{
			size_t start_pos = 0;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
				str.replace(start_pos, from.length(), to);
				start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
			}
		}

		std::string replace_all_copy(const std::string& s, const std::string& f, const std::string& r) {
			if (s.empty() || f.empty() || f == r || f.size() > s.size()) {
				return s;
			}
			std::ostringstream buffer;
			auto start = s.cbegin();
			while (true) {
				const auto end = search(start, s.cend(), f.cbegin(), f.cend());
				copy(start, end, std::ostreambuf_iterator<char>(buffer));
				if (end == s.cend()) {
					break;
				}
				copy(r.cbegin(), r.cend(), std::ostreambuf_iterator<char>(buffer));
				start = end + f.size();
			}
			return buffer.str();
		}


	};



}