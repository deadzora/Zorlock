#include "ZLpch.h"
#include "ZLSLParser.h"


namespace Zorlock {

	bool ZLSLParser::parse_functionbodygeneric_definition(std::string& func_def, functionbodyfunc_definition& fd, size_t numargs)
	{
		return fbodygenparser.process(func_def, fd, numargs);
	}

	bool ZLSLParser::parse_functionbody_definition(std::string& func_def, syntax_definition& fd)
	{
		return fbodyparser.process(func_def, fd);
	}

	std::string ZLSLParser::Parsefunctionbodiess(std::string residual, syntax_definition& fd)
	{
		return std::string();
	}


	bool ZLSLParser::parse_function_definition(std::string& func_def, function_definition& fd)
	{

		return fparser.process(func_def, fd);
	}

	std::string ZLSLParser::Parsefunctions(std::string residual, function_definition& fd)
	{
		int function_count = 0;
		
		if (ZLSLDEBUG == true) printf("Remaining: \n%s\n", residual.c_str());
		do
		{
			if (ZLSLParser::parse_function_definition(residual, fd))
			{
				std::string vars;

				/*
				for (std::size_t i = 0; i < fd.var_list.size(); ++i)
				{
					vars += fd.var_list[i] + ((i < fd.var_list.size() - 1) ? "," : "");
				}
				*/





				//printf("Function[%02d]\n", function_count++);
				//printf("Name: %s\n", fd.name.c_str());
				//printf("Vars: (%s)\n", vars.c_str());
				//printf("Body: \n%s\n", fd.body.c_str());
				//printf("-----------------------------\n\n");

				fd.clear();
			}
			else
				break;
		} while (!residual.empty());

		if (!residual.empty())
		{
			return residual;
		}


	}

	bool ZLSLParser::parse_variable_decl_definition(std::string& var_def, variable_decl_definition& fd)
	{

		return vparser.process(var_def, fd);
	}

	std::string ZLSLParser::ParsevariableDeclares(std::string residual, variable_decl_definition& vd, function_definition& fd, syntax_definition& fbd)
	{
		int function_count = 0;
		//std::string residual = buffer.str();
		if (ZLSLDEBUG == true) printf("Remaining: \n%s\n", residual.c_str());
		do
		{
			if (ZLSLParser::parse_variable_decl_definition(residual, vd))
			{

				ZLSLDeclaredVariables variable;
				variable.command = s_mapStringCommands[vd.command];
				variable.varname = vd.varname;
				variable.vartype = s_mapStringVariables[vd.vartype];
				variable.isArray = vd.isarray;


				if (variable.vartype == VariableTypes::VAR_NONE || variable.vartype == VariableTypes::LIGHTBASE)
				{
					variable.value = vd.vartype;
				}
				if (!vd.index.empty())
				{
					variable.index = std::stoi(vd.index);
				}
				if (variable.isArray) {
					variable.val_list = vd.arrayvals;
				}


				if (variable.command == VarCommandValue::Type)
				{
					if (s_mapStringVariables[vd.vartype] == VariableTypes::PIXEL)
					{
						this->isVertex = false;
					}
				}

				if (this->isVertex)
				{


					if (variable.command == VarCommandValue::Layout)
					{
						variable.varname = vd.varname;
						variable.inout = s_mapStringCommands[vd.inout];
						variable.semantic = SemanticTypes::SEM_NONE;
						if (!vd.semantic.empty())
						{
							variable.issemantic = true;
							variable.semantic = s_mapStringSemantics[vd.semantic];
							if (ZLSLDEBUG == true) printf("Semantic: %s\n", vd.semantic.c_str());
						}
						vlayoutVars.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Z_Struct) {

						variable.value = vd.value;
						variable.size = 0;
						uint32_t occ = 0;
						std::string structbody = vd.value;
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::FLOAT]);
						variable.size += occ * 4;
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::VEC2]);
						variable.size += occ * (4 * 2);
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::VEC3]);
						variable.size += occ * (4 * 3);
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::VEC4]);
						variable.size += occ * (4 * 4);
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::BOOL]);
						variable.size += occ * (1);
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::INT]);
						variable.size += occ * (4);

						vertexStructs.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Pragma_RowMajor)
					{
						vertexdefines.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Z_Define)
					{
						variable.value = vd.value;
						vertexdefines.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Version)
					{
						vertexdefines.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Uniform) {
						if (variable.vartype == VariableTypes::SAMPLER2D)
						{
							vertexSamplers.push_back(variable);
						}
						else {
							vertexUniforms.push_back(variable);
						}
						
					}
					else if (variable.command == VarCommandValue::Out) {
						variable.semantic = SemanticTypes::SEM_NONE;
						if (!vd.semantic.empty())
						{
							variable.issemantic = true;
							variable.inout = s_mapStringCommands[vd.inout];
							variable.semantic = s_mapStringSemantics[vd.semantic];
							if (ZLSLDEBUG == true) printf("Semantic: %s\n", vd.semantic.c_str());
						}

						voutVars.push_back(variable);
					}
					else {
						vertexVars.push_back(variable);
					}

				}
				else {

					if (variable.command == VarCommandValue::Layout)
					{

						variable.varname = vd.varname;
						variable.inout = s_mapStringCommands[vd.inout];
						if (!vd.semantic.empty())
						{
							variable.issemantic = true;
							variable.semantic = s_mapStringSemantics[vd.semantic];
						}
						playoutVars.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Z_Struct) {

						variable.value = vd.value;
						variable.size = 0;
						uint32_t occ = 0;
						std::string structbody = vd.value;
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::FLOAT]);
						variable.size += occ * 4;
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::VEC2]);
						variable.size += occ * (4 * 2);
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::VEC3]);
						variable.size += occ * (4 * 3);
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::VEC4]);
						variable.size += occ * (4 * 4);
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::BOOL]);
						variable.size += occ * (1);
						occ = find_occurance(structbody, s_mapGLSLVariables[VariableTypes::INT]);
						variable.size += occ * (4);

						pixelStructs.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Z_Define)
					{
						variable.value = vd.value;
						pixeldefines.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Pragma_RowMajor)
					{
						pixeldefines.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Version)
					{
						pixeldefines.push_back(variable);
					}
					else if (variable.command == VarCommandValue::In) {

						variable.varname = vd.varname;
						if (!vd.semantic.empty())
						{
							variable.issemantic = true;
							variable.inout = s_mapStringCommands[vd.inout];
							variable.semantic = s_mapStringSemantics[vd.semantic];
						}
						pinVars.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Uniform) {
						if (variable.vartype == VariableTypes::SAMPLER2D)
						{
							pixelSamplers.push_back(variable);
						}
						else {
							pixelUniforms.push_back(variable);
						}						
					}
					else {
						pixelVars.push_back(variable);
					}
				}



				if (ZLSLDEBUG == true) printf("Variable[%02d]\n", function_count++);
				if (ZLSLDEBUG == true) printf("Command: %s\n", vd.command.c_str());
				if (ZLSLDEBUG == true) printf("Variable: (%s)\n", vd.varname.c_str());
				if (ZLSLDEBUG == true) printf("Type: %s\n", vd.vartype.c_str());
				if (ZLSLDEBUG == true) printf("Index: %u\n", variable.index);
				if (ZLSLDEBUG == true) printf("Semantic: %s\n", vd.semantic.c_str());
				if (ZLSLDEBUG == true) printf("-----------------------------\n\n");

				vd.clear();
			}
			else
				if (!residual.empty())
				{
					if (parse_function_definition(residual, fd))
					{
						std::string vars;


						for (std::size_t i = 0; i < fd.var_list.size(); ++i)
						{
							vars += fd.var_list[i].varname + ((i < fd.var_list.size() - 1) ? "," : "");
						}

						ZLSLFunctions func;
						func.returnType = s_mapStringVariables[fd.returntype];
						func.functionName = fd.name;
						func.functionArgVarList = fd.var_list;
						func.functionBody = fd.body;



						if (ZLSLDEBUG == true) printf("Function[%02d]\n", function_count++);
						if (ZLSLDEBUG == true) printf("Name: %s\n", fd.name.c_str());
						if (ZLSLDEBUG == true) printf("Vars: (%s)\n", vars.c_str());
						if (ZLSLDEBUG == true) printf("Body: \n%s\n", fd.body.c_str());
						if (ZLSLDEBUG == true) printf("-----------------------------\n\n");

						std::string fbody = fd.body;
						do {
							if (parse_functionbody_definition(fbody, fbd))
							{
								ZLSLSyntax synt;

								synt.command = s_mapStringCommands[fbd.command];
								synt.variable = IsDeclaredVar(fbd.varname);
								synt.vartype = s_mapStringVariables[fbd.vartype];
								if (synt.variable.empty())
								{
									for (size_t ii = 0; ii < func.functionArgVarList.size(); ii++)
									{
										if (func.functionArgVarList[ii].varname.compare(fbd.varname) == 0)
										{
											synt.variable = func.functionArgVarList[ii].varname;
											break;
										}

									}
								}
								synt.syntax = s_mapSyntaxNames[fbd.syntax];
								synt.operators = s_mapOperatorNames[fbd.syntax];
								std::stringstream(fbd.begin) >> synt.begin;
								std::stringstream(fbd.end) >> synt.end;
								synt.original = fbd.original;
								func.functionBodySyntax.push_back(synt);


								if (ZLSLDEBUG == true) printf("Command: %s\n", fbd.command.c_str());
								if (ZLSLDEBUG == true) printf("Var: (%s)\n", synt.variable.c_str());
								if (ZLSLDEBUG == true) printf("Syntax: (%s)\n", fbd.syntax.c_str());
								if (ZLSLDEBUG == true) printf("Vartype: (%s)\n", fbd.vartype.c_str());
								if (ZLSLDEBUG == true) printf("Begin: (%s)\n", fbd.begin.c_str());
								if (ZLSLDEBUG == true) printf("End: \n%s\n", fbd.end.c_str());
								if (ZLSLDEBUG == true) printf("O: \n%s\n", fbd.original.c_str());
								if (ZLSLDEBUG == true) printf("-----------------------------\n\n");

								fbd.clear();
							}
							else {
								break;
							}
						} while (!fbody.empty());

						if (isVertex)
						{
							vertexFunctions.push_back(func);
						}
						else {
							pixelFunctions.push_back(func);
						}

						fd.clear();
					}
					else {
						break;
					}
				}
				else {
					break;
				}

		} while (!residual.empty());

		if (residual.empty())
		{
			return residual;
		}


	}


	ZLSLParser::ZLSLParser() : isVertex(true)
	{


		MapFunctions();
		MapVariables();
		MapGLSLVariables();
		MapHLSLVariables();

		vparser.parser = this;
		fparser.parser = this;
		fbodyparser.parser = this;
		fbodyfuncparser.parser = this;
	}

	ZLSLParser::~ZLSLParser()
	{
		vertexVars.clear();
		pixelVars.clear();
		vertexFunctions.clear();
		pixelFunctions.clear();

	}

	bool ZLSLParser::Parse(std::string filename)
	{
		std::ifstream t(filename);
		std::stringstream buffer;
		buffer << t.rdbuf();
		lexertk::generator generator;
		if (!generator.process(buffer.str()))
		{
			if (ZLSLDEBUG == true) std::cout << "Shader - Failed to lex: " << buffer.str() << std::endl;
			return 0;
		}
		if (ZLSLDEBUG == true) lexertk::helper::dump(generator);


		if (ZLSLDEBUG == true) std::cout << "***** Shader *****" << std::endl;

		std::string shaderfile = buffer.str();

		shaderfile = ZLSLParser::ParsevariableDeclares(shaderfile, vd, fd, fbd);





		if (ZLSLDEBUG == true) std::cout << "***** End Shader *****" << std::endl;
		return true;
	}

	bool ZLSLParser::ParseString(std::string shader)
	{
		lexertk::generator generator;
		if (!generator.process(shader))
		{
			if (ZLSLDEBUG == true) std::cout << "Example01 - Failed to lex: " << shader << std::endl;
			return 0;
		}
		lexertk::helper::dump(generator);


		if (ZLSLDEBUG == true) std::cout << "***** Shader *****" << std::endl;

		std::string shaderfile = shader;

		shaderfile = ZLSLParser::ParsevariableDeclares(shaderfile, vd, fd, fbd);




		if (ZLSLDEBUG == true) std::cout << "***** End Shader *****" << std::endl;
		return true;
	}

	ZLSLParser::functionbodyfunc_definition& ZLSLParser::ParseFunctionBodyGeneric(std::string func, size_t nofargs)
	{
		fbodygenparser.process(func, fbf, nofargs);
		return fbf;
	}

	ZLSLParser::functionbodyfunc_definition& ZLSLParser::ParseFunctionBody(std::string func)
	{
		fbodyfuncparser.process(func, fbf);
		return fbf;
	}

	std::string ZLSLParser::GetShader(ZLSLParser::OutPutShaderType output, ZLSLParser::ShaderSection section)
	{
		std::string shaderFile;
		std::string EOL = "\n";

		switch (output)
		{
		case OutPutShaderType::GLSL:
		{
			switch (section)
			{
			case ShaderSection::VERTEXSHADER:
			{
				//Add defines at the top
				shaderFile += ReturnGLSLDeclares(vertexdefines);
				//Add custom structs
				shaderFile += ReturnGLSLDeclares(vertexStructs);
				//Next add variable declares
				shaderFile += ReturnGLSLDeclares(vertexVars);
				//start with layout declares
				shaderFile += ReturnGLSLDeclares(vlayoutVars);
				//next add uniforms
				shaderFile += ReturnGLSLDeclares(vertexUniforms);
				//next add samplers
				shaderFile += ReturnGLSLDeclares(vertexSamplers);
				//Next add output declares
				shaderFile += ReturnGLSLDeclares(voutVars);
				//Next add functions
				shaderFile += ReturnGLSLFunctions(vertexFunctions, true);


				break;
			}
			case ShaderSection::FRAGMENTSHADER:
			{
				//Add defines at the top
				shaderFile += ReturnGLSLDeclares(pixeldefines);
				//Add custom structs
				shaderFile += ReturnGLSLDeclares(pixelStructs);
				//Next add variable declares
				shaderFile += ReturnGLSLDeclares(pixelVars);
				//start with layout declares
				shaderFile += ReturnGLSLDeclares(playoutVars);
				//next add in vars
				shaderFile += ReturnGLSLDeclares(pinVars);
				//next add uniforms
				shaderFile += ReturnGLSLDeclares(pixelUniforms);
				//next add samplers
				shaderFile += ReturnGLSLDeclares(pixelSamplers);
				//Next add functions
				shaderFile += ReturnGLSLFunctions(pixelFunctions, false);
				break;
			}
			}
			break;
		}
		case OutPutShaderType::HLSL:
		{
			switch (section)
			{
			case ShaderSection::VERTEXSHADER:
			{
				//Add defines at the top
				shaderFile += ReturnHLSLDeclares(vertexdefines, true);
				//Add custom structs
				shaderFile += ReturnHLSLDeclares(vertexStructs, true);
				//Add constant buffer declares
				shaderFile += ReturnHLSLDeclares(vertexUniforms,true);
				//Add Samplers
				shaderFile += ReturnHLSLDeclares(vertexSamplers, true);
				//next add with some var declares
				shaderFile += ReturnHLSLDeclares(vertexVars,true);
				//start with layout declares
				shaderFile += "struct VS_INPUT" + EOL;
				shaderFile += "{" + EOL;
				shaderFile += ReturnHLSLDeclares(vlayoutVars,true);
				shaderFile += "};" + EOL;
				//Next add output declares
				shaderFile += "struct PS_INPUT" + EOL;
				shaderFile += "{" + EOL;
				shaderFile += ReturnHLSLDeclares(voutVars,true);
				shaderFile += "};" + EOL;
				//Next add functions
				shaderFile += ReturnHLSLFunctions(vertexFunctions, true);
				break;
			}
			case ShaderSection::FRAGMENTSHADER:
			{
				shaderFile += ReturnHLSLDeclares(pixeldefines, false);
				//Add custom structs
				shaderFile += ReturnHLSLDeclares(pixelStructs, false);
				//start with constant buffer declares
				shaderFile += ReturnHLSLDeclares(pixelUniforms,false);
				//Add Samplers
				shaderFile += ReturnHLSLDeclares(pixelSamplers, false);
				//next add with some var declares
				shaderFile += ReturnHLSLDeclares(pixelVars,false);
				//start with input declares
				shaderFile += "struct PS_INPUT" + EOL;
				shaderFile += "{" + EOL;
				shaderFile += ReturnHLSLDeclares(voutVars,false);
				shaderFile += "};" + EOL;
				//Next add functions

				//shaderFile += ReturnHLSLDeclares(playoutVars,false);

				shaderFile += ReturnHLSLFunctions(pixelFunctions, false);
				break;
			}
			}
			break;
		}
		}

		std::string mystring(shaderFile);
		return mystring;
	}

	void ZLSLParser::SaveShader(std::string shaderdata, std::string shaderfile)
	{
		//std::cin >> shaderdata;
		std::ofstream out(shaderfile);
		out << shaderdata;
		out.close();
	}



	std::string ZLSLParser::ReturnGLSLFunctions(std::vector< ZLSLFunctions> funcs, bool isvert)
	{
		std::string functions;
		std::string EOL = "\n";

		functions += EOL;

		for (size_t i = 0; i < funcs.size(); i++)
		{

			functions += s_mapGLSLVariables[funcs[i].returnType] + " " + funcs[i].functionName + "(";
			for (size_t a = 0; a < funcs[i].functionArgVarList.size(); a++)
			{
				functions += s_mapGLSLVariables[funcs[i].functionArgVarList[a].vartype] + " " + funcs[i].functionArgVarList[a].varname + " ";
				if (a < funcs[i].functionArgVarList.size() - 1)
				{
					functions += ",";
				}

			}
			functions += ")" + EOL;
			functions += "{" + EOL;
			functions += ReturnGLSLFunctionBody(funcs[i], isvert); //funcs[i].functionBody;
			functions += "}" + EOL;
			functions += EOL;


		}
		return functions;
	}

	std::string ZLSLParser::ReturnGLSLFunctionBody(ZLSLFunctions func, bool isvert)
	{
		std::string fbody = func.functionBody;
		std::string EOL = "\n";

		for (size_t i = 0; i < func.functionBodySyntax.size(); i++)
		{
			if (ZLSLDEBUG == true) printf("Function body Command: %d \n", func.functionBodySyntax[i].command);
			//check commands
			if (func.functionBodySyntax[i].command != VarCommandValue::COM_NONE)
			{

				if (func.functionBodySyntax[i].command == VarCommandValue::Z_Return)
				{
					if (!func.functionBodySyntax[i].variable.empty())
					{
						if (isvert == true)
						{
							std::string zr = "gl_Position=" + func.functionBodySyntax[i].variable + ";"+EOL;
							ReplaceAll(fbody, func.functionBodySyntax[i].original, zr);
							

						}
						else {
							ReplaceAll(fbody, func.functionBodySyntax[i].original, EOL);

						}
					}
				}
				else if (func.functionBodySyntax[i].command == VarCommandValue::Texture)
				{
					if (ZLSLDEBUG == true) printf("Texture is : %s \n", func.functionBodySyntax[i].varname.c_str());
				}
				else if (func.functionBodySyntax[i].command == VarCommandValue::Z_Mul)
				{
					fbf.clear();
					ParseFunctionBodyGeneric(func.functionBodySyntax[i].original,2);
					//printf("Function : %s args %s val list size: %i \n", fbf.name.c_str(), fbf.arguments[0].varname.c_str(), fbf.arguments.size());
					
					

					std::string finalf = fbf.arguments[0].arithmetic+"*"+ fbf.arguments[1].arithmetic;
					
					if (ZLSLDEBUG == true) printf("Process Texture Function : %s \n", finalf.c_str());
					ReplaceAll(fbody, func.functionBodySyntax[i].original, finalf);




				}
			}
			else if (func.functionBodySyntax[i].vartype != VariableTypes::VAR_NONE)
			{
				//change delcares - not needed since ZLSL uses same declares as GLSL
				//ReplaceAll(fbody, s_mapGLSLVariables[func.functionBodySyntax[i].variable->vartype], s_mapGLSLVariables[func.functionBodySyntax[i].variable->vartype]);
			}
			else if (!func.functionBodySyntax[i].variable.empty())
			{
				//remap variable names, we only need to do this for the struct vars in HLSL in the main function

				if (isvert)
				{
					/*
					if (s_mapFunctionNames[func.functionName] == FunctionNames::MAIN)
					{
						for (size_t ii = 0; ii < vlayoutVars.size(); ii++)
						{
							printf("Replacing vars : %d \n", ii);
							fbody = replace_all_copy(fbody, vlayoutVars[ii].varname, "input."+vlayoutVars[ii].varname);
						}
						for (size_t ii = 0; ii < voutVars.size(); ii++)
						{
							printf("Replacing vars : %d \n", ii);
							fbody = replace_all_copy(fbody, voutVars[ii].varname, "output." + voutVars[ii].varname);
						}
					}
					*/
				}


			}


		}
		return fbody;
	}

	std::string ZLSLParser::ReturnHLSLFunctions(std::vector<ZLSLFunctions> funcs, bool isvert)
	{
		std::string functions;
		std::string EOL = "\n";

		for (size_t i = 0; i < funcs.size(); i++)
		{
			if (s_mapFunctionNames[funcs[i].functionName] == FunctionNames::MAIN)
			{
				if (isvert)
				{
					functions += "PS_INPUT " + funcs[i].functionName + "(VS_INPUT input";
					if (funcs[i].functionArgVarList.size() > 0)
					{
						functions += ", ";
					}
				}
				else {

					functions += "float4 " + funcs[i].functionName + "(PS_INPUT input";
					if (funcs[i].functionArgVarList.size() > 0)
					{
						functions += ", ";
					}

				}
			}
			else {
				functions += s_mapHLSLVariables[funcs[i].returnType] + " " + funcs[i].functionName + "(";
			}
			for (size_t a = 0; a < funcs[i].functionArgVarList.size(); a++)
			{
				functions += s_mapHLSLVariables[funcs[i].functionArgVarList[a].vartype] + " " + funcs[i].functionArgVarList[a].varname + " ";
				if (a < funcs[i].functionArgVarList.size() - 1)
				{
					functions += ",";
				}

			}
			if (!isvert)
			{
				functions += ") : SV_Target" + EOL;
			}
			else {
				functions += ")" + EOL;
			}
			//functions += "{" + EOL;
			functions += ReturnHLSLFunctionBody(funcs[i], isvert);
			//functions += "}" + EOL;
			functions += EOL;


		}
		return functions;
	}

	std::string ZLSLParser::ReturnHLSLFunctionBody(ZLSLFunctions func, bool isvert)
	{
		std::string fbody = func.functionBody;
		std::string EOL = "\n";

		for (size_t i = 0; i < func.functionBodySyntax.size(); i++)
		{
			//check commands
			if (func.functionBodySyntax[i].command != VarCommandValue::COM_NONE)
			{
				if (func.functionBodySyntax[i].command == VarCommandValue::Z_Return)
				{
					if (!func.functionBodySyntax[i].variable.empty())
					{
						if (isvert == true)
						{
							std::string zr = "return output;" + EOL;
							//ReplaceAll(fbody, "{", "");
							//ReplaceAll(fbody, "}", "");
							ReplaceAll(fbody, func.functionBodySyntax[i].original, zr);
							fbody = "{" + EOL + "	PS_INPUT output = (PS_INPUT) 0; " + EOL + fbody + EOL + "}" + EOL;


						}
						else {
							std::string zr = "return " + func.functionBodySyntax[i].variable + ";" + EOL;
							//ReplaceAll(fbody, "{", "");
							//ReplaceAll(fbody, "}", "");
							ReplaceAll(fbody, func.functionBodySyntax[i].original, zr);
							fbody = "{" + EOL + ReturnHLSLDeclares(playoutVars,false) + EOL + fbody + EOL + "}" + EOL;
						}
						
					}
				}
				else if (func.functionBodySyntax[i].command == VarCommandValue::Texture)
				{
					if (ZLSLDEBUG == true) printf("Process Texture Function : %s \n", func.functionBodySyntax[i].original.c_str());
					fbf.clear();
					ParseFunctionBodyGeneric(func.functionBodySyntax[i].original, 2);

					//ParseFunctionBody(func.functionBodySyntax[i].original);
					if (ZLSLDEBUG == true) printf("Function : %s nof args %i   \n", fbf.name.c_str(),fbf.arguments.size());
					std::string newfuncbody = "";
					bool isarray = false;

					
					
					if (fbf.arguments[0].isArray)
					{
						newfuncbody += fbf.arguments[0].arithmetic + "[NonUniformResourceIndex("+ fbf.arguments[0].val_list[0] +")].Sample(" + fbf.arguments[0].arithmetic + "Sampler,";
						newfuncbody += fbf.arguments[1].arithmetic + ") ";
					}
					else {
						newfuncbody += fbf.arguments[0].arithmetic + ".Sample(" + fbf.arguments[0].arithmetic + "Sampler,";
						newfuncbody += fbf.arguments[1].arithmetic + ") ";
					}


					

						

					if (ZLSLDEBUG == true) printf("Function : %s \n", newfuncbody.c_str());
					ReplaceAll(fbody, func.functionBodySyntax[i].original, newfuncbody);
					
				}
				else if (func.functionBodySyntax[i].command == VarCommandValue::Z_Mul)
				{
					fbf.clear();
					ParseFunctionBodyGeneric(func.functionBodySyntax[i].original, 2);

					if (ZLSLDEBUG == true) printf("Function : %s nof args %i   \n", fbf.name.c_str(), fbf.arguments.size());
					if (ZLSLDEBUG == true) printf("Process Multiply Function : %s \n", func.functionBodySyntax[i].original.c_str());
					std::string newfuncbody = "";
					newfuncbody += "mul("+fbf.arguments[0].arithmetic + "," + fbf.arguments[1].arithmetic + ")";

					//ReplaceAll(fbody, "Z_Mul", s_mapHLSLCommands[func.functionBodySyntax[i].command]);
					ReplaceAll(fbody, func.functionBodySyntax[i].original, newfuncbody);
					lexertk::generator generator;
					if (generator.process(fbody))
					{
						for (size_t ii = 0; ii < generator.size(); ii++)
						{
							if (s_mapStringVariables[generator[ii].value] != VariableTypes::VAR_NONE)
							{
								fbody = replace_all_copy(fbody, s_mapGLSLVariables[s_mapStringVariables[generator[ii].value]], s_mapHLSLVariables[s_mapStringVariables[generator[ii].value]]);
								
							}
							
						}
					}

					
				}
				//parse_functiontexture_definition_impl
			}
			else if (func.functionBodySyntax[i].vartype != VariableTypes::VAR_NONE)
			{
				//change delcares - change declares from GLSL style to HLSL
				if (ZLSLDEBUG == true) printf("Replacing decls : %s to %s \n", s_mapGLSLVariables[func.functionBodySyntax[i].vartype].c_str(), s_mapHLSLVariables[func.functionBodySyntax[i].vartype].c_str());

				fbody = replace_all_copy(fbody, s_mapGLSLVariables[func.functionBodySyntax[i].vartype], s_mapHLSLVariables[func.functionBodySyntax[i].vartype]);
			}
			else if (!func.functionBodySyntax[i].variable.empty())
			{
				//remap variable names, we only need to do this for the struct vars in HLSL in the main function




			}




		}
		if (isvert)
		{
			if (ZLSLDEBUG == true) printf("Replacing vars in  : %s \n", func.functionName.c_str());
			if (s_mapFunctionNames[func.functionName] == FunctionNames::MAIN)
			{
				for (size_t ii = 0; ii < vlayoutVars.size(); ii++)
				{
					if (ZLSLDEBUG == true) printf("Replacing vars : %d \n", ii);
					fbody = replace_all_copy(fbody, vlayoutVars[ii].varname, "input." + vlayoutVars[ii].varname);
				}
				for (size_t ii = 0; ii < voutVars.size(); ii++)
				{
					if (ZLSLDEBUG == true) printf("Replacing vars : %d \n", ii);
					fbody = replace_all_copy(fbody, voutVars[ii].varname, "output." + voutVars[ii].varname);
				}
			}
		}
		else {
			if (ZLSLDEBUG == true) printf("Replacing vars in  : %s \n", func.functionName.c_str());
			if (s_mapFunctionNames[func.functionName] == FunctionNames::MAIN)
			{

				for (size_t ii = 0; ii < voutVars.size(); ii++)
				{
					if (ZLSLDEBUG == true) printf("Replacing vars : %d \n", ii);
					fbody = replace_all_copy(fbody, voutVars[ii].varname, "input." + voutVars[ii].varname);
				}
			}
		}
		return fbody;
	}

	std::string ZLSLParser::GetDeclareType(std::string& varname)
	{

		return "";
	}

	std::string ZLSLParser::GetDeclareValue(std::string& varname)
	{
		for (size_t i = 0; i < vertexdefines.size(); i++)
		{
			if (vertexdefines[i].varname.compare(varname) == 0)
			{

				return vertexdefines[i].value;
			}
		}
		for (size_t i = 0; i < vertexVars.size(); i++)
		{
			if (vertexVars[i].varname.compare(varname) == 0)
			{

				return vertexVars[i].value;
			}
		}
		for (size_t i = 0; i < vlayoutVars.size(); i++)
		{
			if (vlayoutVars[i].varname.compare(varname) == 0)
			{

				return vlayoutVars[i].value;
			}
		}
		for (size_t i = 0; i < voutVars.size(); i++)
		{
			if (voutVars[i].varname.compare(varname) == 0)
			{
				return voutVars[i].value;
			}
		}
		for (size_t i = 0; i < vertexUniforms.size(); i++)
		{
			if (vertexUniforms[i].varname.compare(varname) == 0)
			{
				return vertexUniforms[i].value;
			}
		}
		for (size_t i = 0; i < pixeldefines.size(); i++)
		{
			if (pixeldefines[i].varname.compare(varname) == 0)
			{

				return pixeldefines[i].value;
			}
		}
		for (size_t i = 0; i < pixelVars.size(); i++)
		{
			if (pixelVars[i].varname.compare(varname) == 0)
			{
				return pixelVars[i].value;
			}
		}
		for (size_t i = 0; i < playoutVars.size(); i++)
		{
			if (playoutVars[i].varname.compare(varname) == 0)
			{

				return playoutVars[i].value;
			}
		}
		for (size_t i = 0; i < pinVars.size(); i++)
		{
			if (pinVars[i].varname.compare(varname) == 0)
			{

				return pinVars[i].value;
			}
		}
		for (size_t i = 0; i < pixelUniforms.size(); i++)
		{
			if (pixelUniforms[i].varname.compare(varname) == 0)
			{
				return pixelUniforms[i].value;
			}
		}

		if (ZLSLDEBUG == true) printf("Could not find variable name \n");
		return "";
	}

	uint32_t ZLSLParser::GetSamplerIndex(std::string varname)
	{
		uint32_t index = 0;
		for (size_t i = 0; i < pixelUniforms.size(); i++)
		{
			if (pixelUniforms[i].vartype == VariableTypes::SAMPLER2D)
			{
				if (pixelUniforms[i].varname.compare(varname) == 0)
				{
					return index;
				}
				else {
					index++;
				}
			}
		}
		return index;
	}


	std::string ZLSLParser::IsDeclaredVar(std::string& varname)
	{


		for (size_t i = 0; i < vertexVars.size(); i++)
		{
			if (vertexVars[i].varname.compare(varname) == 0)
			{

				return varname;
			}
		}
		for (size_t i = 0; i < vlayoutVars.size(); i++)
		{
			if (vlayoutVars[i].varname.compare(varname) == 0)
			{

				return varname;
			}
		}
		for (size_t i = 0; i < voutVars.size(); i++)
		{
			if (voutVars[i].varname.compare(varname) == 0)
			{
				return varname;
			}
		}
		for (size_t i = 0; i < vertexUniforms.size(); i++)
		{
			if (vertexUniforms[i].varname.compare(varname) == 0)
			{
				return varname;
			}
		}
		for (size_t i = 0; i < pixelVars.size(); i++)
		{
			if (pixelVars[i].varname.compare(varname) == 0)
			{
				return varname;
			}
		}
		for (size_t i = 0; i < playoutVars.size(); i++)
		{
			if (playoutVars[i].varname.compare(varname) == 0)
			{

				return varname;
			}
		}
		for (size_t i = 0; i < pinVars.size(); i++)
		{
			if (pinVars[i].varname.compare(varname) == 0)
			{

				return varname;
			}
		}
		for (size_t i = 0; i < pixelUniforms.size(); i++)
		{
			if (pixelUniforms[i].varname.compare(varname) == 0)
			{
				return varname;
			}
		}

		if (ZLSLDEBUG == true) printf("Could not find variable name \n");
		return "";
	}






	std::string ZLSLParser::ReturnGLSLDeclares(std::vector<ZLSLDeclaredVariables> dec)
	{
		std::string declares;
		std::string EOL = "\n";

		for (size_t i = 0; i < dec.size(); i++)
		{

			switch (dec[i].command)
			{
			case VarCommandValue::Z_Struct:
			{
				declares += s_mapGLSLCommands[dec[i].command] + " " + dec[i].varname + EOL;
				declares += "{" + EOL;
				std::string structbody = dec[i].value;
				declares += "	" + structbody + EOL;
				declares += "};" + EOL;

				break;
			}
			case VarCommandValue::Type:
			{
				declares += "//type " + s_mapGLSLVariables[dec[i].vartype] + EOL;
				break;
			}
			case VarCommandValue::Z_Define:
			{
				declares += s_mapGLSLCommands[dec[i].command] + " " + dec[i].varname + " " + dec[i].value + EOL;
				break;
			}
			case VarCommandValue::Version:
			{
				declares += "#version " + std::to_string(dec[i].index) + " " + dec[i].varname + EOL;
				break;
			}
			case VarCommandValue::Layout:
			{

				declares += "layout(location = " + std::to_string(dec[i].index) + ") " + s_mapGLSLCommands[dec[i].inout] + " " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
				break;
			}

			case VarCommandValue::Uniform:
			{

				if (dec[i].vartype != VariableTypes::VAR_NONE)
				{

					if (dec[i].isArray)
					{
						if (dec[i].val_list.size() > 0)
						{
							declares += "uniform " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + "[" + dec[i].val_list[0] + "]" + ";" + EOL;
							
						}
						else {
							declares += "uniform " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + "[" + std::to_string(dec[i].index) + "]" + ";" + EOL;
						}
					}
					else {
						declares += "uniform " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;

					}

				}
				else {
					if (dec[i].isArray)
					{
						if (dec[i].val_list.size() > 0)
						{
							declares += "uniform " + dec[i].value + " " + dec[i].varname + "[" + dec[i].val_list[0] + "]" + ";" + EOL;
						}
						else {
							declares += "uniform " + dec[i].value + " " + dec[i].varname + "[" + std::to_string(dec[i].index) + "]" + ";" + EOL;						
						}
					}
					else {
						declares += "uniform " + dec[i].value + " " + dec[i].varname + ";" + EOL;

					}
				}


				break;
			}

			case VarCommandValue::Out:
			{
				declares += s_mapGLSLCommands[VarCommandValue::Out] + " " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
				break;
			}

			case VarCommandValue::In:
			{
				declares += s_mapGLSLCommands[VarCommandValue::In] + " " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
				break;
			}

			case VarCommandValue::Attribute:
			{
				declares += s_mapGLSLCommands[VarCommandValue::Attribute] + " " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
				break;
			}

			case VarCommandValue::Varying:
			{
				declares += s_mapGLSLCommands[VarCommandValue::Attribute] + " " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
				break;
			}

			}
		}

		return declares;
	}

	std::string ZLSLParser::ReturnHLSLDeclares(std::vector<ZLSLDeclaredVariables> dec,bool isvert)
	{
		std::string declares;
		std::string EOL = "\n";

		for (size_t i = 0; i < dec.size(); i++)
		{
			switch (dec[i].command)
			{
			case VarCommandValue::Z_Struct:
			{
				declares += s_mapHLSLCommands[dec[i].command] + " " + dec[i].varname + EOL;
				declares += "{" + EOL;
				lexertk::generator generator;
				std::string structbody = dec[i].value;
				if (generator.process(structbody))
				for (size_t ii = 0; ii < generator.size(); ii++)
				{
					if (s_mapStringVariables[generator[ii].value] != VariableTypes::VAR_NONE)
					{
						structbody = replace_all_copy(structbody, s_mapGLSLVariables[s_mapStringVariables[generator[ii].value]], s_mapHLSLVariables[s_mapStringVariables[generator[ii].value]]);

					}

				}
				
				declares += "	"+structbody + EOL;
				declares += "};" + EOL;

				break;
			}
			case VarCommandValue::Z_Define:
			{
				declares += s_mapHLSLCommands[dec[i].command] + " " + dec[i].varname + " " + dec[i].value +  EOL;
				break;
			}
			case VarCommandValue::Pragma_RowMajor:
			{
				declares += s_mapHLSLCommands[dec[i].command] + "( " + dec[i].varname + " )" + EOL;
				break;
			}
			case VarCommandValue::Type:
			{
				declares += "//type " + s_mapHLSLVariables[dec[i].vartype] + EOL;
				break;
			}

			case VarCommandValue::Version:
			{
				declares += "//version " + std::to_string(dec[i].index) + " " + dec[i].varname + EOL;
				break;
			}

			case VarCommandValue::Layout:
			{

				if (dec[i].issemantic!=SemanticTypes::SEM_NONE)
				{
					if (!s_mapHLSLLayouts[dec[i].semantic].empty())
					{
						declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + " : " + s_mapHLSLLayouts[dec[i].semantic] + ";" + EOL;
					}
					else {
						declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
					}
					
				}
				else {
					declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
				}
				break;
			}

			case VarCommandValue::Uniform:
			{
				switch (dec[i].vartype)
				{
				case VariableTypes::SAMPLER2D:
				{
					dec[i].index = GetSamplerIndex(dec[i].varname);
					if (dec[i].isArray)
					{
						
						declares += s_mapHLSLVariables[dec[i].vartype] + "<float4> " + dec[i].varname + "["+dec[i].val_list[0]+"] : TEXTURE : register(t" + std::to_string(GetSamplerIndex(dec[i].varname)) + ");" + EOL;
						declares += "SamplerState " + dec[i].varname + "Sampler : SAMPLER : register(s" + std::to_string(GetSamplerIndex(dec[i].varname)) + ");" + EOL;
					}
					else {
						declares += s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + " : TEXTURE : register(t" + std::to_string(GetSamplerIndex(dec[i].varname)) + ");" + EOL;
						declares += "SamplerState " + dec[i].varname + "Sampler : SAMPLER : register(s" + std::to_string(GetSamplerIndex(dec[i].varname)) + ");" + EOL;
					}

					break;
				}
				case VariableTypes::SAMPLERCUBE:
				{
					break;
				}

				default:
				{				
					if (isvert)
					{
						dec[i].index = vertexuniformcount;
						declares += "cbuffer c_" + dec[i].varname + "_buffer : register(b" + std::to_string(vertexuniformcount) + ")" + EOL;
					}
					else {
						dec[i].index = vertexuniformcount + fragmentuniformcount;
						declares += "cbuffer c_" + dec[i].varname + "_buffer : register(b" + std::to_string(vertexuniformcount+ fragmentuniformcount) + ")" + EOL;
					}
					
					declares += "{" + EOL;
					if (dec[i].vartype!=VariableTypes::VAR_NONE && dec[i].vartype != VariableTypes::LIGHTBASE)
					{
						//declares += s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
						if (dec[i].val_list.size() > 0)
						{
							if (dec[i].isArray)
							{
								declares += s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + "[" + dec[i].val_list[0] + "];" + EOL;
							}
							else {
								declares += s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
							}

						}
						else {
							if (dec[i].isArray)
							{
								declares += s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + "[" + std::to_string(dec[i].index) + "];" + EOL;
							}
							else {
								declares += s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
							}
							
						}
					}
					else if(dec[i].vartype == VariableTypes::VAR_NONE || dec[i].vartype == VariableTypes::LIGHTBASE) {
						//probably custom struct declare, use original value.
						if (dec[i].val_list.size() > 0)
						{
							if (dec[i].isArray)
							{
								declares += dec[i].value + " " + dec[i].varname + "["+ dec[i].val_list[0] +"];" + EOL;
							}
							else {
								declares += dec[i].value + " " + dec[i].varname + ";" + EOL;
							}
							
						}
						else {
							if (dec[i].isArray)
							{
								declares += dec[i].value + " " + dec[i].varname + "[" + std::to_string(dec[i].index) + "];" + EOL;
								
							}
							else {
								declares += dec[i].value + " " + dec[i].varname + ";" + EOL;
							}
							
						}
					}

					declares += "};" + EOL;
					if (isvert)
					{
						vertexuniformcount++;
					}
					else {
						fragmentuniformcount++;
					}

					break;
				}
				}

				break;
			}

			case VarCommandValue::Out:
			{
				if (dec[i].issemantic!=SemanticTypes::SEM_NONE)
				{
					if (!s_mapHLSLLayouts[dec[i].semantic].empty())
					{
						if (dec[i].semantic == SemanticTypes::POSITION)
						{
							declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + " : SV_" + s_mapHLSLLayouts[dec[i].semantic] + ";" + EOL;
						}
						else {
							declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + " : " + s_mapHLSLLayouts[dec[i].semantic] + ";" + EOL;
						}
					}
					else {
						declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
					}
				}
				else {
					declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
				}
				break;
			}

			case VarCommandValue::In:
			{
				if (dec[i].issemantic != SemanticTypes::SEM_NONE)
				{
					if (!s_mapHLSLLayouts[dec[i].semantic].empty())
					{ 
						if (dec[i].semantic == SemanticTypes::POSITION)
						{
							declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + " : SV_" + s_mapHLSLLayouts[dec[i].semantic] + ";" + EOL;
						}
						else {
							declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + " : " + s_mapHLSLLayouts[dec[i].semantic] + ";" + EOL;
						}
						
					}
					else {
						declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
					}
				}
				else {
					declares += "	" + s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
				}
				break;
			}

			}
		}


		return declares;
	}



	void ZLSLParser::MapFunctions()
	{
		s_mapFunctionNames["main"] = FunctionNames::MAIN;

		s_mapNameFunctions[FunctionNames::NO_MAIN] = "";
		s_mapNameFunctions[FunctionNames::MAIN] = "main";
	}

	void ZLSLParser::MapVariables()
	{
		s_mapStringCommands[""] = COM_NONE;
		s_mapStringCommands["uniform"] = Uniform;
		s_mapStringCommands["varying"] = Varying;
		s_mapStringCommands["attribute"] = Attribute;
		s_mapStringCommands["out"] = Out;
		s_mapStringCommands["in"] = In;
		s_mapStringCommands["type"] = Type;
		s_mapStringCommands["version"] = Version;
		s_mapStringCommands["const"] = Constant;
		s_mapStringCommands["layout"] = Layout;
		s_mapStringCommands["function"] = Function;
		s_mapStringCommands["Z_Return"] = Z_Return;
		s_mapStringCommands["texture"] = Texture;
		s_mapStringCommands["int"] = Int;
		s_mapStringCommands["Z_Mul"] = Z_Mul;
		s_mapStringCommands["define"] = Z_Define;
		s_mapStringCommands["struct"] = Z_Struct;
		s_mapStringCommands["for"] = For;
		s_mapStringCommands["pragma_matrix"] = Pragma_RowMajor;

		s_mapStringVariables[""] = VAR_NONE;
		s_mapStringVariables["float"] = FLOAT;
		s_mapStringVariables["int"] = INT;
		s_mapStringVariables["bool"] = BOOL;
		s_mapStringVariables["vec2"] = VEC2;
		s_mapStringVariables["vec3"] = VEC3;
		s_mapStringVariables["vec4"] = VEC4;
		s_mapStringVariables["bvec2"] = BVEC2;
		s_mapStringVariables["bvec3"] = BVEC3;
		s_mapStringVariables["bvec4"] = BVEC4;
		s_mapStringVariables["ivec2"] = IVEC2;
		s_mapStringVariables["ivec3"] = IVEC3;
		s_mapStringVariables["ivec4"] = IVEC4;
		s_mapStringVariables["mat2"] = MAT2;
		s_mapStringVariables["mat3"] = MAT3;
		s_mapStringVariables["mat4"] = MAT4;
		s_mapStringVariables["sampler2D"] = SAMPLER2D;
		s_mapStringVariables["samplerCube"] = SAMPLERCUBE;
		s_mapStringVariables["void"] = VARVOID;
		s_mapStringVariables["vertex"] = VARVERTEX;
		s_mapStringVariables["fragment"] = PIXEL;
		s_mapStringVariables["core"] = CORE;
		s_mapStringVariables["lightbase"] = LIGHTBASE;


		s_mapStringSemantics[""] = SEM_NONE;
		s_mapStringSemantics["Z_Position"] = POSITION;
		s_mapStringSemantics["Z_Color"] = SCOLOR;
		s_mapStringSemantics["Z_Texcoord"] = TEXCOORD;
		s_mapStringSemantics["Z_Normal"] = NORMAL;
		s_mapStringSemantics["Z_Binormal"] = BINORMAL;
		s_mapStringSemantics["Z_Blendweight"] = BLENDWEIGHT;
		s_mapStringSemantics["Z_Blendindices"] = BLENDINDICES;
		s_mapStringSemantics["Z_TPositon"] = POSITIONT;
		s_mapStringSemantics["Z_Tangent"] = TANGENT;
		s_mapStringSemantics["Z_Fog"] = FOG;
		s_mapStringSemantics["Z_Face"] = VFACE;
		s_mapStringSemantics["Z_Size"] = PSIZE;
		s_mapStringSemantics["Z_WorldPosition"] = WORLD_POSITION;

		s_mapOperatorNames[""] = ShaderOperators::OP_NONE;
		s_mapOperatorNames["*"] = ShaderOperators::MULT;
		s_mapOperatorNames["-"] = ShaderOperators::SUBT;
		s_mapOperatorNames["/"] = ShaderOperators::DIVID;
		s_mapOperatorNames["+"] = ShaderOperators::ADDIT;
		s_mapOperatorNames["%"] = ShaderOperators::MODU;
		s_mapOperatorNames["!"] = ShaderOperators::NOTEQ;
		s_mapOperatorNames["="] = ShaderOperators::OPEQUAL;


	}

	void ZLSLParser::MapGLSLVariables()
	{

		s_mapGLSLVariables[FLOAT] = "float";
		s_mapGLSLVariables[INT] = "int";
		s_mapGLSLVariables[BOOL] = "bool";
		s_mapGLSLVariables[VEC2] = "vec2";
		s_mapGLSLVariables[VEC3] = "vec3";
		s_mapGLSLVariables[VEC4] = "vec4";
		s_mapGLSLVariables[BVEC2] = "bvec2";
		s_mapGLSLVariables[BVEC3] = "bvec3";
		s_mapGLSLVariables[BVEC4] = "bvec4";
		s_mapGLSLVariables[IVEC2] = "ivec2";
		s_mapGLSLVariables[IVEC3] = "ivec3";
		s_mapGLSLVariables[IVEC4] = "ivec4";
		s_mapGLSLVariables[MAT2] = "mat2";
		s_mapGLSLVariables[MAT3] = "mat3";
		s_mapGLSLVariables[MAT4] = "mat4";
		s_mapGLSLVariables[SAMPLER2D] = "sampler2D";
		s_mapGLSLVariables[SAMPLERCUBE] = "samplerCube";
		s_mapGLSLVariables[VARVOID] = "void";
		s_mapGLSLVariables[VARVERTEX] = "vertex";
		s_mapGLSLVariables[PIXEL] = "fragment";
		s_mapGLSLVariables[LIGHTBASE] = "lightbase";

		s_mapGLSLCommands[Uniform] = "uniform";
		s_mapGLSLCommands[Attribute] = "attribute";
		s_mapGLSLCommands[Out] = "out";
		s_mapGLSLCommands[In] = "in";
		s_mapGLSLCommands[Constant] = "const";
		s_mapGLSLCommands[Varying] = "varying";
		s_mapGLSLCommands[Z_Define] = "#define";
		s_mapGLSLCommands[Z_Struct] = "struct";
		s_mapGLSLCommands[Pragma_RowMajor] = "";
		//globals
		s_mapGLSLCommands[Z_Position] = "gl_Position";
		s_mapGLSLCommands[Z_PointSize] = "gl_PointSize";
		s_mapGLSLCommands[Z_FragColor] = "gl_FragColor";
		s_mapGLSLCommands[Z_FragData] = "gl_FragData";
		s_mapGLSLCommands[Z_FragCoord] = "gl_FragCoord";
		s_mapGLSLCommands[Z_FrontFacing] = "gl_FrontFacing";
		s_mapGLSLCommands[Z_PointCoord] = "gl_PointCoord";
		s_mapGLSLCommands[Z_FragDepth] = "gl_FragDepth";
		s_mapGLSLCommands[Z_Mul] = "";

		s_mapGLSLLayouts[POSITION] = "";
		s_mapGLSLLayouts[SCOLOR] = "";
		s_mapGLSLLayouts[TEXCOORD] = "";
		s_mapGLSLLayouts[NORMAL] = "";
		s_mapGLSLLayouts[BINORMAL] = "";
		s_mapGLSLLayouts[BLENDWEIGHT] = "";
		s_mapGLSLLayouts[BLENDINDICES] = "";
		s_mapGLSLLayouts[POSITIONT] = "";
		s_mapGLSLLayouts[TANGENT] = "";
		s_mapGLSLLayouts[WORLD_POSITION] = "";
		s_mapGLSLLayouts[FOG] = "";
		s_mapGLSLLayouts[VFACE] = "";
		s_mapGLSLLayouts[PSIZE] = "";


	}

	void ZLSLParser::MapHLSLVariables()
	{
		s_mapHLSLVariables[FLOAT] = "float";
		s_mapHLSLVariables[INT] = "int";
		s_mapHLSLVariables[BOOL] = "bool";
		s_mapHLSLVariables[VEC2] = "float2";
		s_mapHLSLVariables[VEC3] = "float3";
		s_mapHLSLVariables[VEC4] = "float4";
		s_mapHLSLVariables[BVEC2] = "bool2";
		s_mapHLSLVariables[BVEC3] = "bool3";
		s_mapHLSLVariables[BVEC4] = "bool4";
		s_mapHLSLVariables[IVEC2] = "int2";
		s_mapHLSLVariables[IVEC3] = "int3";
		s_mapHLSLVariables[IVEC4] = "int4";
		s_mapHLSLVariables[MAT2] = "float2x2";
		s_mapHLSLVariables[MAT3] = "float3x3";
		s_mapHLSLVariables[MAT4] = "row_major float4x4";
		s_mapHLSLVariables[SAMPLER2D] = "Texture2D";
		s_mapHLSLVariables[SAMPLERCUBE] = "TextureCube";
		s_mapHLSLVariables[VARVOID] = "void";
		s_mapHLSLVariables[LIGHTBASE] = "lightbase";

		s_mapHLSLCommands[Uniform] = "";
		s_mapHLSLCommands[Attribute] = "";
		s_mapHLSLCommands[Out] = "VS_OUTPUT";
		s_mapHLSLCommands[In] = "VS_INPUT";
		s_mapHLSLCommands[Constant] = "static const";
		s_mapHLSLCommands[Varying] = "";
		s_mapHLSLCommands[Z_Define] = "#define";
		s_mapHLSLCommands[Z_Struct] = "struct";
		s_mapHLSLCommands[Pragma_RowMajor] = "#pragma pack_matrix";
		//globals
		s_mapHLSLCommands[Z_Position] = "SV_POSITION";
		s_mapHLSLCommands[Z_PointSize] = "PSIZE";
		s_mapHLSLCommands[Z_FragColor] = "SV_TARGET";
		s_mapHLSLCommands[Z_FragData] = "SV_TARGET";
		s_mapHLSLCommands[Z_FragCoord] = "SV_POSITION";
		s_mapHLSLCommands[Z_FrontFacing] = "SV_ISFRONTFACE";
		s_mapHLSLCommands[Z_PointCoord] = "SV_POSITION";
		s_mapHLSLCommands[Z_FragDepth] = "SV_DEPTH";
		s_mapHLSLCommands[Z_Mul] = "mul";

		s_mapHLSLLayouts[SEM_NONE] = "";
		s_mapHLSLLayouts[POSITION] = "POSITION";
		s_mapHLSLLayouts[SCOLOR] = "COLOR";
		s_mapHLSLLayouts[TEXCOORD] = "TEXCOORD";
		s_mapHLSLLayouts[NORMAL] = "NORMAL";
		s_mapHLSLLayouts[BINORMAL] = "BINORMAL";
		s_mapHLSLLayouts[BLENDWEIGHT] = "BLENDWEIGHT";
		s_mapHLSLLayouts[BLENDINDICES] = "BLENDINDICES";
		s_mapHLSLLayouts[POSITIONT] = "POSITIONT";
		s_mapHLSLLayouts[TANGENT] = "TANGENT";
		s_mapHLSLLayouts[FOG] = "FOG";
		s_mapHLSLLayouts[VFACE] = "VFACE";
		s_mapHLSLLayouts[PSIZE] = "PSIZE";
		s_mapHLSLLayouts[WORLD_POSITION] = "WORLD_POSITION";
		
	}

	void ZLSLParser::MapSyntax()
	{
		s_mapSyntaxNames["radians"] = RADIANS;
		s_mapSyntaxNames["degrees"] = DEGREES;
		s_mapSyntaxNames["sin"] = SIN;
		s_mapSyntaxNames["cos"] = COS;
		s_mapSyntaxNames["tan"] = TAN;
		s_mapSyntaxNames["asin"] = ASIN;
		s_mapSyntaxNames["acos"] = ACOS;
		s_mapSyntaxNames["atan"] = ATAN;
		s_mapSyntaxNames["pow"] = POW;
		s_mapSyntaxNames["exp"] = EXP;
		s_mapSyntaxNames["min"] = MIN;
		s_mapSyntaxNames["log"] = LOG;
		s_mapSyntaxNames["sqrt"] = SQRT;
		s_mapSyntaxNames["isqrt"] = RSQRT;
		s_mapSyntaxNames["abs"] = ABS;
		s_mapSyntaxNames["sign"] = SIGN;
		s_mapSyntaxNames["floor"] = FLOOR;
		s_mapSyntaxNames["ceil"] = CEIL;
		s_mapSyntaxNames["fract"] = FRACT;
		s_mapSyntaxNames["mod"] = MOD;
		s_mapSyntaxNames["max"] = MAX;
		s_mapSyntaxNames["clamp"] = CLAMP;
		s_mapSyntaxNames["mix"] = MIX;
		s_mapSyntaxNames["step"] = STEP;
		s_mapSyntaxNames["smstep"] = SMSTEP;
		s_mapSyntaxNames["length"] = LENGTH;
		s_mapSyntaxNames["distance"] = DIST;
		s_mapSyntaxNames["dot"] = DOT;
		s_mapSyntaxNames["cross"] = CROSS;
		s_mapSyntaxNames["normalize"] = NORMALIZE;
		s_mapSyntaxNames["fforward"] = FFOWARD;
		s_mapSyntaxNames["reflect"] = REFLECT;
		s_mapSyntaxNames["refract"] = REFRACT;
		s_mapSyntaxNames["lessthan"] = LESSTHAN;
		s_mapSyntaxNames["lessthaneq"] = LESSTHANEQ;
		s_mapSyntaxNames["greaterthan"] = GREATERTHAN;
		s_mapSyntaxNames["greaterthaneq"] = GREATERTHANEQ;
		s_mapSyntaxNames["equal"] = SYNEQUAL;
		s_mapSyntaxNames["notequal"] = NOTEQUAL;
		s_mapSyntaxNames["any"] = ANY;
		s_mapSyntaxNames["all"] = ALL;
		s_mapSyntaxNames["not"] = NOT;
		s_mapSyntaxNames[""] = SYNTAX_NONE;

	}

	bool ZLSLParser::parse_function_definition_impl::process(std::string& func_def, function_definition& fd)
	{


		if (!init(func_def))
			return false;

		if (!token_is(token_t::e_symbol, "function"))
			return false;

		if (!token_is_then_assign(token_t::e_symbol, fd.returntype))
			return false;

		if (!token_is_then_assign(token_t::e_symbol, fd.name))
			return false;

		if (!token_is(token_t::e_lbracket))
			return false;

		if (!token_is(token_t::e_rbracket))
		{
			std::vector<ZLSLDeclaredVariables> var_list;

			for (; ; )
			{
				ZLSLDeclaredVariables vars;
				// (x,y,z,....w)
				std::string vtype;
				if (!token_is_then_assign(token_t::e_symbol, vtype))
					return false;
				vars.vartype = parser->s_mapStringVariables[vtype];
				if (!token_is_then_assign(token_t::e_symbol, vars.varname))
					return false;

				if (token_is(token_t::e_rbracket))
					break;

				if (!token_is(token_t::e_comma))
					return false;
				var_list.push_back(vars);
			}

			var_list.swap(fd.var_list);
		}

		std::size_t body_begin = current_token().position;
		std::size_t body_end = current_token().position;

		

		if (!token_is(token_t::e_lcrlbracket, e_hold))
			return false;
		int bracket_stack = 0;
		for (; ; )
		{
			body_end = current_token().position;

			if (token_is(token_t::e_lcrlbracket))
				bracket_stack++;
			else if (token_is(token_t::e_rcrlbracket))
			{
				bracket_stack--;
				if (0 == bracket_stack)
					break;
			}
			else
			{
				if (lexer().finished())
					return false;

				next_token();
			}
		}

		std::size_t size = body_end - body_begin + 1;

		fd.body = func_def.substr(body_begin+2, size-3);
		if (ZLSLDEBUG == true) printf("NEW BODY: %s \n", fd.body.c_str());
		const std::size_t index = body_begin + size;

		if (index < func_def.size())
			func_def = func_def.substr(index, func_def.size() - index);
		else
			func_def = "";

		return true;
	}

	bool ZLSLParser::parse_variable_decl_definition_impl::process(std::string& var_def, variable_decl_definition& fd)
	{

		if (!init(var_def))
			return false;

		switch (parser->s_mapStringCommands[current_token().value])
		{
		case Z_Struct:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return false;
			if (token_is(token_t::e_lcrlbracket))
			{
				//just grab vars inside and process later
				size_t arthbegin = current_token().position;
				do {
					next_token();
				} while (current_token().type!=token_t::e_rcrlbracket);
				size_t arthend = current_token().position-1;
				std::string arith = var_def.substr(arthbegin, arthend - arthbegin);
				if (ZLSLDEBUG == true) printf("Arithmetic Arg %s \n", arith.c_str());

				fd.value = arith;
				next_token();
				next_token();
				if (ZLSLDEBUG == true) printf("Next token is %s \n", current_token().value.c_str());
			}
			else {
				return false;
			}

			
			break;
		}
		case Pragma_RowMajor:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return false;
			break;
		}
		case Z_Define:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return false;
			if (!token_is_then_assign(token_t::e_number, fd.value))
				return false;
			break;
		}
		case Uniform:
		{

			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			if (ZLSLDEBUG == true) printf("UNIFORM %s \n", fd.command.c_str());
			//switch (s_mapStringVariables[current_token().value])
			if (!token_is_then_assign(token_t::e_symbol, fd.vartype))
				return false;

			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return false;
			//printf("Layout location %s \n", current_token().value.c_str());
			if (!token_is(token_t::e_eof))
			{
				if (!token_is(token_t::e_lsqrbracket))
					return false;
				if (current_token().type != token_t::e_number)
				{
					fd.isarray = true;
					fd.arrayvals.push_back(current_token().value);
					fd.arrayvals.push_back(parser->GetDeclareValue(fd.arrayvals[0]));
					if (ZLSLDEBUG == true) printf("ARRAY FOUND: %s count %s \n", fd.varname.c_str(), fd.arrayvals[0].c_str());
					next_token();
				}
				else {
					fd.isarray = true;					
					//should try to pack definition value
					fd.arrayvals.push_back(current_token().value);
					if (ZLSLDEBUG == true) printf("ARRAY FOUND: %s count %s \n", fd.varname.c_str(), fd.arrayvals[0].c_str());
					next_token();
				}

				if (!token_is(token_t::e_rsqrbracket))
					return false;
			}
			else {
				break;
			}
			if (!token_is(token_t::e_eof))
				return false;
			break;
		}
		case Varying:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			break;
		}
		case Attribute:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			break;
		}
		case Out:
		{
			fd.semantic = "";
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			//switch (s_mapStringVariables[current_token().value])
			if (!token_is_then_assign(token_t::e_symbol, fd.vartype))
				return false;

			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return false;
			if (!token_is(token_t::e_eof))
			{
				if (!token_is(token_t::e_symbol))
					return false;

				if (!token_is_then_assign(token_t::e_symbol, fd.semantic))
					return false;
			}
			else {
				fd.semantic = "";
				break;
			}
			if (!token_is(token_t::e_eof))
				return false;
			break;

		}
		case In:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			//switch (s_mapStringVariables[current_token().value])
			if (!token_is_then_assign(token_t::e_symbol, fd.vartype))
				return false;
			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return false;
			if (!token_is(token_t::e_eof))
				return false;

			fd.semantic = "";
			break;
		}
		case Type:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			if (!token_is_then_assign(token_t::e_symbol, fd.vartype))
				return false;
			break;
		}
		case Version:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			if (!token_is_then_assign(token_t::e_number, fd.index))
				return false;
			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return false;
			break;
		}
		case Constant:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;

			//switch (s_mapStringVariables[current_token().value])
			if (!token_is_then_assign(token_t::e_symbol, fd.vartype))
				return false;

			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return false;
			if (!token_is(token_t::e_eof))
				return false;

			break;
		}
		case Layout:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
			if (!token_is(token_t::e_lbracket))
				return false;
			if (!token_is(token_t::e_rbracket))
			{

				if (!token_is(token_t::e_symbol, "location"))
					return false;

				//fd.varname = "location";
				if (!token_is(token_t::e_eq))
					return false;
				if (!token_is_then_assign(token_t::e_number, fd.index))
					//if (!token_is(token_t::e_number))
					return false;

				//printf("Layout location %s \n", current_token().value);
				//advance_token(token_advance_mode::e_advance);

			}
			if (!token_is(token_t::e_rbracket))
				return false;
			if (!token_is_then_assign(token_t::e_symbol, fd.inout)) // in or out.. need to record
				return false;
			//get in out

			if (!token_is_then_assign(token_t::e_symbol, fd.vartype))
				return false;

			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return false;
			if (!token_is(token_t::e_eof))
			{
				if (!token_is(token_t::e_symbol))
					return false;

				if (!token_is_then_assign(token_t::e_symbol, fd.semantic))
					return false;
			}
			else {
				break;
			}
			if (!token_is(token_t::e_eof))
				return false;
			break;
		}
		case Function:
		{

			if (ZLSLDEBUG == true) printf("FUNCTION FOUND: %s\n", current_token().value.c_str());
			std::size_t body_begin = current_token().position;




			if (ZLSLDEBUG == true) printf("Remaining size: %d Index %d \n", var_def.length(), body_begin);
			if (body_begin < var_def.length())
				var_def = var_def.substr(body_begin, var_def.length() - body_begin);
			else
				var_def = "";
			return false;
			break;
		}

		}
		//next_token();
		std::size_t body_begin = current_token().position;




		if (ZLSLDEBUG == true) printf("Remaining size: %d Index %d \n", var_def.length(), body_begin);
		if (body_begin < var_def.length())
			var_def = var_def.substr(body_begin, var_def.length() - body_begin);
		else
			var_def = "";
		return true;
	}

	bool ZLSLParser::parse_funcbody_decl_definition_impl::ParseToken(syntax_definition& fd)
	{




		next_token();
		return true;
	}


	bool ZLSLParser::parse_funcbody_decl_definition_impl::process(std::string& var_def, syntax_definition& fd)
	{
		if (!init(var_def))
			return false;


		//check if command.
		if (parser->s_mapStringCommands[current_token().value] != COM_NONE)
		{


			fd.command = current_token().value;
			fd.begin = std::to_string(var_def.size() - current_token().position);
			if (ZLSLDEBUG == true) printf("Command: %s begin %s \n", fd.command.c_str(), fd.begin.c_str());
			switch (parser->s_mapStringCommands[fd.command])
			{
			case Z_Return:
			{
				size_t bodybegin = 0;
				size_t bodyend = 0;
				bodybegin = current_token().position;
				if (ZLSLDEBUG == true) printf("is Z Return \n");
				next_token();
				if (!token_is(token_t::e_lbracket))
					return false;
				if (ZLSLDEBUG == true) printf("Left Bracket \n");
				if (!token_is_then_assign(token_t::e_symbol, fd.varname))
					return false;
				if (ZLSLDEBUG == true) printf("Command: %s var %s \n", fd.command.c_str(), fd.varname.c_str());
				if (!token_is(token_t::e_rbracket))
					return false;
				if (!token_is(token_t::e_eof))
					return false;
				fd.end = std::to_string(current_token().position);
				bodyend = current_token().position;
				fd.original = var_def.substr(bodybegin, bodyend - bodybegin);
				if (ZLSLDEBUG == true) printf("Command: %s end %d \n", fd.command.c_str(), fd.end.c_str());
				break;
			}
			case Texture:
			{	
				size_t bodybegin = 0;
				size_t bodyend = 0;
				 
				bodybegin = current_token().position;
				if (ZLSLDEBUG == true) printf("is Texture Function \n");
				next_token();

				if (!token_is(token_t::e_lbracket))
					return false;
				size_t nofbrackets = 1;
				do {
					ZLSLDeclaredVariables vars;
					vars.varname = current_token().value;
					fd.var_list.push_back(vars);
					if (ZLSLDEBUG == true) printf("Token: %s  \n", current_token().value.c_str());
					next_token();
					if (current_token().type == token_t::e_lbracket)
					{
						nofbrackets++;
					}
					if (current_token().type == token_t::e_rbracket)
					{
						nofbrackets--;
					}
				} while (nofbrackets>0);
				next_token();
				bodyend = current_token().position;
				fd.end = std::to_string(bodyend);
				fd.original = var_def.substr(bodybegin, bodyend - bodybegin);

				break;
			}
			case Z_Mul:
			{
				size_t bodybegin = 0;
				size_t bodyend = 0;
				bodybegin = current_token().position;
				if (ZLSLDEBUG == true) printf("is Multiply Function \n");
				next_token();

				if (!token_is(token_t::e_lbracket))
					return false;
				size_t nofbrackets = 1;
				do {
					ZLSLDeclaredVariables vars;
					vars.varname = current_token().value;
					fd.var_list.push_back(vars);
					if (ZLSLDEBUG == true) printf("Token: %s  \n", current_token().value.c_str());
					next_token();
					if (current_token().type == token_t::e_lbracket)
					{
						nofbrackets++;
					}
					if (current_token().type == token_t::e_rbracket)
					{
						nofbrackets--;
					}
				} while (nofbrackets > 0);
				next_token();
				bodyend = current_token().position;
				fd.end = std::to_string(bodyend);
				fd.original = var_def.substr(bodybegin, bodyend - bodybegin);

				break;
			}
			}


		}
		else if (parser->s_mapStringVariables[current_token().value] != VAR_NONE) 
		{
			if (ZLSLDEBUG == true) printf("Variable Declare: %s\n", current_token().value.c_str());

			fd.vartype = current_token().value;
			//next_token();
			if (token_is(token_t::e_lbracket))
			{
				return true;
				//must be a declare with constructor - copy args
				//capture
				/*
				size_t varbegin = current_token().position;	
				size_t nofbrackets = 1;
				do {
					if (ZLSLDEBUG == true) printf("Token: %s  \n", current_token().value.c_str());
					next_token();
					if (current_token().type == token_t::e_lbracket)
					{
						nofbrackets++;
					}
					if (current_token().type == token_t::e_rbracket)
					{
						nofbrackets--;
					}
				} while (nofbrackets > 0);
				size_t varend = current_token().position;
				fd.original = var_def.substr(varend, varend - varend);
				*/
			}
			else if (token_is(token_t::e_lsqrbracket))
			{
				fd.vartype = "";
				return true;
				
			}
			else if (token_is(token_t::e_lcrlbracket))
			{
				fd.vartype = "";
				return true;

			}
			else if (token_is(token_t::e_rcrlbracket))
			{
				fd.vartype = "";
				return true;

			}
			else if (token_is(token_t::e_number))
			{
				fd.vartype = "";
				return true;
				
			}


			if (!token_is_then_assign(token_t::e_symbol, fd.varname))
				return true;



		}
		else if (parser->s_mapSyntaxNames[current_token().value] != SYNTAX_NONE) {
			if (ZLSLDEBUG == true) printf("Syntax: %s\n", current_token().value.c_str());

			fd.syntax = current_token().value;

		}
		else if (parser->s_mapOperatorNames[current_token().value] != OP_NONE)
		{


			fd.syntax = current_token().value;
			if (ZLSLDEBUG == true) printf("Syntax: operator %s\n", current_token().value.c_str());



		}
		else if (current_token().type == lexertk::parser_helper::token_t::e_symbol) {
			std::string v = current_token().value;
			fd.varname = parser->IsDeclaredVar(v);


			//fd.varname = current_token().value
		}
		next_token();


		std::size_t body_begin = current_token().position;
		if (ZLSLDEBUG == true) printf("Remaining size: %i Index %i \n", var_def.length(), body_begin);
		if (body_begin < var_def.length())
			var_def = var_def.substr(body_begin, var_def.length() - body_begin);
		else
			var_def = "";


		return true;
	}

	bool ZLSLParser::parse_functionbodyfunc_definition_impl::process(std::string& func_def, functionbodyfunc_definition& fd)
	{
		if (!init(func_def))
			return false;
		size_t nofargs = 2;
		fd.name = current_token().value;
		next_token();
		if (!token_is(token_t::e_lbracket))
			return false;
		size_t nofbrackets = 1;
		do 
		{
			size_t capturea = current_token().position;
			ZLSLDeclaredVariables var;
			if (!token_is_then_assign(token_t::e_symbol, var.varname))
				return false;
			
			
			//var.varname = current_token().value;
			if (ZLSLDEBUG == true) printf("Function Arg %s \n", var.varname.c_str());
			nofargs--;

			if (nofargs < 0)
				break;
			if (token_is(token_t::e_lsqrbracket))
			{
				nofbrackets++;
				var.isArray = true;
				//next_token();
				size_t arrbegin = current_token().position;
				do {
					next_token();
				} while (!token_is(token_t::e_rsqrbracket));

				size_t arrend = current_token().position-1;

				
				std::string arga = func_def.substr(arrbegin, arrend - arrbegin);
				if (ZLSLDEBUG == true) printf("Array Arg %s \n", arga.c_str());
				var.val_list.push_back(arga);

				next_token();
				if (!token_is(token_t::e_comma))
				{
					size_t arthbegin= current_token().position;
					//could be some math here or the end of the function
					if (token_is(token_t::e_rbracket))
					{
						nofbrackets--;
						break;
					}
					//wasn't end of function, grab arithmetic
					do {
						next_token();
					} while (!token_is(token_t::e_rbracket));
					nofbrackets--;
					size_t arthend = current_token().position-2;
					std::string arith = func_def.substr(arthbegin, arthend - arthbegin);
					if (ZLSLDEBUG == true) printf("Arithmetic Arg %s \n", arith.c_str());
					var.arithmetic = arith;
					fd.arguments.push_back(var);
				}



				
			}
			
			
			
			if (current_token().type != token_t::e_comma)
			{
				if (current_token().type == token_t::e_rbracket)
				{
					nofbrackets--;
				}
				else {
					break;
				}
			}
			else {
				size_t captureb = current_token().position - 1;
				if (!var.arithmetic.empty())
				{
					var.arithmetic = func_def.substr(capturea, captureb - capturea);
				}
				next_token();
			}

			
			fd.arguments.push_back(var);

		} while (nofbrackets > 0);



		return true;
	}
	bool ZLSLParser::parse_functionbodygeneric_definition_impl::process(std::string& func_def, functionbodyfunc_definition& fd, size_t nofargs)
	{
		if (!init(func_def))
			return false;
		fd.name = current_token().value;
		next_token();
		if (!token_is(token_t::e_lbracket))
			return false;
		size_t nofbrackets = 1;
		size_t capturea = 0;
		size_t captureb = 0;
		ZLSLDeclaredVariables * var = 0;
		var = new ZLSLDeclaredVariables();
		capturea = current_token().position;
		
		do {
			

			if (current_token().type == token_t::e_lsqrbracket)
			{
				//beginning of an array, capture variable name
				captureb = current_token().position;
				std::string arith = func_def.substr(capturea, captureb - capturea);
				if (ZLSLDEBUG == true) printf("Arithmetic Arg %s \n", arith.c_str());
				var->arithmetic = arith;

				size_t capturearr = current_token().position+1;
				//get array arguments
				size_t nofsqrbrackets = 1;
				do {
					next_token();

					if (current_token().type == token_t::e_lsqrbracket)
					{
						nofsqrbrackets++;
					}
					if (current_token().type == token_t::e_rsqrbracket)
					{
						nofsqrbrackets--;
					}

				} while (nofsqrbrackets > 0);

				size_t capturearrend = current_token().position;
				std::string arrayargs = func_def.substr(capturearr, capturearrend - capturearr);
				var->isArray = true;
				var->val_list.push_back(arrayargs);
			}

			if (current_token().type == token_t::e_lbracket)
			{
				nofbrackets++;
			}

			if (current_token().type == token_t::e_rbracket)
			{
				nofbrackets--;
				if (nofbrackets == 0)
				{
					captureb = current_token().position;
					

					std::string arith = func_def.substr(capturea, captureb - capturea);
					if (ZLSLDEBUG == true) printf("Arithmetic Arg %s \n", arith.c_str());
					var->arithmetic = arith;

					fd.arguments.push_back(*var);
					return true;
				}
			}

			if (nofbrackets == 1)
			{
				if (current_token().type == token_t::e_comma)
				{
					//if is array we already captured the main var name.
					if (!var->isArray)
					{
						captureb = current_token().position;
						std::string arith = func_def.substr(capturea, captureb - capturea);
						if (ZLSLDEBUG == true) printf("Arithmetic Arg %s \n", arith.c_str());
						var->arithmetic = arith;
					}
					fd.arguments.push_back(*var);
					next_token();
					capturea = current_token().position;
					var = new ZLSLDeclaredVariables();
					nofargs--;
				}
			}
			next_token();
		} while (nofbrackets > 0);


		return true;
	}
}