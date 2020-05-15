#include "ZLpch.h"
#include "ZLSLParser.h"


namespace Zorlock {
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
		//std::string residual = buffer.str();
		printf("Remaining: \n%s\n", residual.c_str());
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





				printf("Function[%02d]\n", function_count++);
				printf("Name: %s\n", fd.name.c_str());
				//printf("Vars: (%s)\n", vars.c_str());
				printf("Body: \n%s\n", fd.body.c_str());
				printf("-----------------------------\n\n");

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
		//printf("Remaining: \n%s\n", residual.c_str());
		do
		{
			if (ZLSLParser::parse_variable_decl_definition(residual, vd))
			{

				ZLSLDeclaredVariables variable;
				variable.command = s_mapStringCommands[vd.command];
				variable.varname = vd.varname;
				variable.vartype = s_mapStringVariables[vd.vartype];
				std::stringstream indexnum(vd.index);
				indexnum >> variable.index;
				variable.isArray = vd.isarray;

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
							printf("Semantic: %s\n", vd.semantic.c_str());
						}
						vlayoutVars.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Uniform) {
						vertexUniforms.push_back(variable);
					}
					else if (variable.command == VarCommandValue::Out) {
						variable.semantic = SemanticTypes::SEM_NONE;
						if (!vd.semantic.empty())
						{
							variable.issemantic = true;
							variable.inout = s_mapStringCommands[vd.inout];
							variable.semantic = s_mapStringSemantics[vd.semantic];
							printf("Semantic: %s\n", vd.semantic.c_str());
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
						pixelUniforms.push_back(variable);
					}
					else {
						pixelVars.push_back(variable);
					}
				}



				printf("Variable[%02d]\n", function_count++);
				printf("Command: %s\n", vd.command.c_str());
				printf("Variable: (%s)\n", vd.varname.c_str());
				printf("Type: \n%s\n", vd.vartype.c_str());
				printf("Index: \n%s\n", vd.index.c_str());
				printf("Semantic: \n%s\n", vd.semantic.c_str());
				printf("-----------------------------\n\n");

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



						printf("Function[%02d]\n", function_count++);
						printf("Name: %s\n", fd.name.c_str());
						printf("Vars: (%s)\n", vars.c_str());
						printf("Body: \n%s\n", fd.body.c_str());
						printf("-----------------------------\n\n");

						std::string fbody = fd.body;
						do {
							if (parse_functionbody_definition(fbody, fbd))
							{
								ZLSLSyntax synt;

								synt.command = s_mapStringCommands[fbd.command];
								synt.variable = IsDeclaredVar(fbd.varname);

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
								std::stringstream(fbd.begin) >> synt.begin;
								std::stringstream(fbd.end) >> synt.end;

								func.functionBodySyntax.push_back(synt);


								printf("Command: %s\n", fbd.command.c_str());
								printf("Var: (%s)\n", synt.variable.c_str());
								printf("Syntax: (%s)\n", fbd.syntax.c_str());
								printf("Vartype: (%s)\n", fbd.vartype.c_str());
								printf("Begin: (%s)\n", fbd.begin.c_str());
								printf("End: \n%s\n", fbd.end.c_str());
								printf("O: \n%s\n", fbd.original.c_str());
								printf("-----------------------------\n\n");

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
			std::cout << "Example01 - Failed to lex: " << buffer.str() << std::endl;
			return 0;
		}
		lexertk::helper::dump(generator);


		std::cout << "***** Shader *****" << std::endl;

		std::string shaderfile = buffer.str();

		shaderfile = ZLSLParser::ParsevariableDeclares(shaderfile, vd, fd, fbd);





		std::cout << "***** End Shader *****" << std::endl;
		return true;
	}

	bool ZLSLParser::ParseString(std::string shader)
	{
		lexertk::generator generator;
		if (!generator.process(shader))
		{
			std::cout << "Example01 - Failed to lex: " << shader << std::endl;
			return 0;
		}
		lexertk::helper::dump(generator);


		std::cout << "***** Shader *****" << std::endl;

		std::string shaderfile = shader;

		shaderfile = ZLSLParser::ParsevariableDeclares(shaderfile, vd, fd, fbd);




		std::cout << "***** End Shader *****" << std::endl;
		return true;
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
				//Next add variable declares
				shaderFile += ReturnGLSLDeclares(vertexVars);
				//start with layout declares
				shaderFile += ReturnGLSLDeclares(vlayoutVars);
				//next add uniforms
				shaderFile += ReturnGLSLDeclares(vertexUniforms);
				//Next add output declares
				shaderFile += ReturnGLSLDeclares(voutVars);
				//Next add functions
				shaderFile += ReturnGLSLFunctions(vertexFunctions, true);


				break;
			}
			case ShaderSection::FRAGMENTSHADER:
			{
				//Next add variable declares
				shaderFile += ReturnGLSLDeclares(pixelVars);
				//start with layout declares
				shaderFile += ReturnGLSLDeclares(playoutVars);
				//next add in vars
				shaderFile += ReturnGLSLDeclares(pinVars);
				//next add uniforms
				shaderFile += ReturnGLSLDeclares(pixelUniforms);
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
				//start with constant buffer declares
				shaderFile += ReturnHLSLDeclares(vertexUniforms);
				//next add with some var declares
				shaderFile += ReturnHLSLDeclares(vertexVars);
				//start with layout declares
				shaderFile += "struct VS_INPUT" + EOL;
				shaderFile += "{" + EOL;
				shaderFile += ReturnHLSLDeclares(vlayoutVars);
				shaderFile += "};" + EOL;
				//Next add output declares
				shaderFile += "struct VS_OUTPUT" + EOL;
				shaderFile += "{" + EOL;
				shaderFile += ReturnHLSLDeclares(voutVars);
				shaderFile += "};" + EOL;
				//Next add functions
				shaderFile += ReturnHLSLFunctions(vertexFunctions, true);
				break;
			}
			case ShaderSection::FRAGMENTSHADER:
			{
				//start with constant buffer declares
				shaderFile += ReturnHLSLDeclares(pixelUniforms);
				//next add with some var declares
				shaderFile += ReturnHLSLDeclares(pixelVars);
				//start with input declares
				shaderFile += "struct VS_INPUT" + EOL;
				shaderFile += "{" + EOL;
				shaderFile += ReturnHLSLDeclares(voutVars);
				shaderFile += "};" + EOL;
				//Next add functions

				shaderFile += "/*Change function body return type to " + ReturnHLSLDeclares(playoutVars);
				shaderFile += "*/" + EOL;
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
			//functions += "{" + EOL;
			functions += ReturnGLSLFunctionBody(funcs[i], isvert); //funcs[i].functionBody;
			//functions += "}" + EOL;
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
			printf("Function body Command: %d \n", func.functionBodySyntax[i].command);
			//check commands
			if (func.functionBodySyntax[i].command != VarCommandValue::COM_NONE)
			{

				if (func.functionBodySyntax[i].command == VarCommandValue::Z_Return)
				{
					if (!func.functionBodySyntax[i].variable.empty())
					{
						if (isvert == true)
						{
							printf("ZL_Return is : %s \n", func.functionBodySyntax[i].varname.c_str());
							std::string bodyA = func.functionBody.substr(0, fbody.size() - func.functionBodySyntax[i].begin);
							std::string bodyB = func.functionBody.substr(fbody.size() - func.functionBodySyntax[i].end, func.functionBody.size());
							//switch variable semantic here
							fbody = bodyA + "gl_Position=" + func.functionBodySyntax[i].variable + ";" + EOL + bodyB;
						}
						else {
							printf("ZL_Return is : %s \n", func.functionBodySyntax[i].varname.c_str());
							std::string bodyA = func.functionBody.substr(0, fbody.size() - func.functionBodySyntax[i].begin);
							std::string bodyB = func.functionBody.substr(fbody.size() - func.functionBodySyntax[i].end, func.functionBody.size());
							//switch variable semantic here
							fbody = bodyA + EOL + bodyB;
						}
					}
				}
				else if (func.functionBodySyntax[i].command == VarCommandValue::Texture)
				{
					printf("Texture is : %s \n", func.functionBodySyntax[i].varname.c_str());
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
					functions += "VS_OUTPUT  " + funcs[i].functionName + "(VS_INPUT input";
					if (funcs[i].functionArgVarList.size() > 0)
					{
						functions += ", ";
					}
				}
				else {

					functions += "float " + funcs[i].functionName + "(VS_INPUT input";
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


							std::string bodyA = func.functionBody.substr(0, fbody.size() - func.functionBodySyntax[i].begin);
							ReplaceAll(bodyA, "{", "");
							std::string bodyB = func.functionBody.substr(fbody.size() - func.functionBodySyntax[i].end, func.functionBody.size());
							ReplaceAll(bodyB, "}", "");
							
							//switch variable semantic here
							fbody = "{" + EOL + "	VS_OUTPUT output = (VS_OUTPUT) 0;" + EOL + bodyA + "return output;" + EOL + bodyB + EOL + "}" + EOL;
						}
						else {

							
							std::string bodyA = func.functionBody.substr(0, fbody.size() - func.functionBodySyntax[i].begin);
							ReplaceAll(bodyA, "{", "");
							std::string bodyB = func.functionBody.substr(fbody.size() - func.functionBodySyntax[i].end, func.functionBody.size());
							ReplaceAll(bodyB, "}", "");

							//switch variable semantic here
							fbody = "{" + EOL + ReturnHLSLDeclares(playoutVars) + EOL + bodyA + "return "+ func.functionBodySyntax[i].variable+";" + EOL + bodyB + EOL + "}" + EOL;
							
							//add layout declare here
							//fbody = "{" + EOL + ReturnHLSLDeclares(playoutVars) + EOL + fbody + EOL + "return "+ func.functionBodySyntax[i].variable+";" + EOL +"}" + EOL;

						}
					}
				}
			}
			else if (func.functionBodySyntax[i].vartype != VariableTypes::VAR_NONE)
			{
				//change delcares - change declares from GLSL style to HLSL
				printf("Replacing decls : %d \n", i);
				fbody = replace_all_copy(fbody, s_mapGLSLVariables[func.functionBodySyntax[i].vartype], s_mapHLSLVariables[func.functionBodySyntax[i].vartype]);
			}
			else if (!func.functionBodySyntax[i].variable.empty())
			{
				//remap variable names, we only need to do this for the struct vars in HLSL in the main function




			}




		}
		if (isvert)
		{
			printf("Replacing vars in  : %s \n", func.functionName.c_str());
			if (s_mapFunctionNames[func.functionName] == FunctionNames::MAIN)
			{
				for (size_t ii = 0; ii < vlayoutVars.size(); ii++)
				{
					printf("Replacing vars : %d \n", ii);
					fbody = replace_all_copy(fbody, vlayoutVars[ii].varname, "input." + vlayoutVars[ii].varname);
				}
				for (size_t ii = 0; ii < voutVars.size(); ii++)
				{
					printf("Replacing vars : %d \n", ii);
					fbody = replace_all_copy(fbody, voutVars[ii].varname, "output." + voutVars[ii].varname);
				}
			}
		}
		return fbody;
	}

	std::string ZLSLParser::GetDeclareType(std::string& varname)
	{

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

		printf("Could not find variable name \n");
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
			case VarCommandValue::Type:
			{
				declares += "//type " + s_mapGLSLVariables[dec[i].vartype] + EOL;
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
				if (dec[i].isArray)
				{
					declares += "uniform " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + "[" + std::to_string(dec[i].index) + "]" + ";" + EOL;
				}
				else {
					declares += "uniform " + s_mapGLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;

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

	std::string ZLSLParser::ReturnHLSLDeclares(std::vector<ZLSLDeclaredVariables> dec)
	{
		std::string declares;
		std::string EOL = "\n";

		for (size_t i = 0; i < dec.size(); i++)
		{
			switch (dec[i].command)
			{
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

					if (dec[i].isArray)
					{
						declares += s_mapHLSLVariables[dec[i].vartype] + "Array " + dec[i].varname + " : TEXTURE : register(t" + std::to_string(GetSamplerIndex(dec[i].varname)) + ");" + EOL;
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
					declares += "cbuffer c_" + dec[i].varname + "_buffer : register(b" + std::to_string(i) + ")" + EOL;
					declares += "{" + EOL;
					declares += s_mapHLSLVariables[dec[i].vartype] + " " + dec[i].varname + ";" + EOL;
					declares += "};" + EOL;
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
		s_mapStringCommands[""] = COM_NONE;

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
		s_mapStringVariables[""] = VAR_NONE;

		s_mapStringSemantics["Z_Position"] = POSITION;
		s_mapStringSemantics["Z_Color"] = COLOR;
		s_mapStringSemantics["Z_Texcoord"] = TEXCOORD;
		s_mapStringSemantics["Z_Normal"] = NORMAL;
		s_mapStringSemantics["Z_Binormal"] = BINORMAL;
		s_mapStringSemantics["Z_Blendweight"] = BLENDWEIGHT;
		s_mapStringSemantics["Z_Blendindices"] = BLENDINDICES;
		s_mapStringSemantics["Z_TPositon"] = POSITIONT;
		s_mapStringSemantics["Z_Tangent"] = TANGENT;
		s_mapStringSemantics["Z_Fog"] = FOG;
		s_mapStringSemantics["Z_Face"] = VFACE;
		s_mapStringSemantics[""] = SEM_NONE;

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

		s_mapGLSLCommands[Uniform] = "uniform";
		s_mapGLSLCommands[Attribute] = "attribute";
		s_mapGLSLCommands[Out] = "out";
		s_mapGLSLCommands[In] = "in";
		s_mapGLSLCommands[Constant] = "const";
		s_mapGLSLCommands[Varying] = "varying";

		//globals
		s_mapGLSLCommands[Z_Position] = "gl_Position";
		s_mapGLSLCommands[Z_PointSize] = "gl_PointSize";
		s_mapGLSLCommands[Z_FragColor] = "gl_FragColor";
		s_mapGLSLCommands[Z_FragData] = "gl_FragData";
		s_mapGLSLCommands[Z_FragCoord] = "gl_FragCoord";
		s_mapGLSLCommands[Z_FrontFacing] = "gl_FrontFacing";
		s_mapGLSLCommands[Z_PointCoord] = "gl_PointCoord";
		s_mapGLSLCommands[Z_FragDepth] = "gl_FragDepth";

		s_mapGLSLLayouts[POSITION] = "";
		s_mapGLSLLayouts[COLOR] = "";
		s_mapGLSLLayouts[TEXCOORD] = "";
		s_mapGLSLLayouts[NORMAL] = "";
		s_mapGLSLLayouts[BINORMAL] = "";
		s_mapGLSLLayouts[BLENDWEIGHT] = "";
		s_mapGLSLLayouts[BLENDINDICES] = "";
		s_mapGLSLLayouts[POSITIONT] = "";
		s_mapGLSLLayouts[TANGENT] = "";
		s_mapGLSLLayouts[FOG] = "";
		s_mapGLSLLayouts[VFACE] = "";



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
		s_mapHLSLVariables[MAT4] = "float4x4";
		s_mapHLSLVariables[SAMPLER2D] = "Texture2D";
		s_mapHLSLVariables[SAMPLERCUBE] = "TextureCube";
		s_mapHLSLVariables[VARVOID] = "void";

		s_mapHLSLCommands[Uniform] = "";
		s_mapHLSLCommands[Attribute] = "";
		s_mapHLSLCommands[Out] = "VS_OUTPUT";
		s_mapHLSLCommands[In] = "VS_INPUT";
		s_mapHLSLCommands[Constant] = "static const";
		s_mapHLSLCommands[Varying] = "";

		//globals
		s_mapHLSLCommands[Z_Position] = "SV_POSITION";
		s_mapHLSLCommands[Z_PointSize] = "PSIZE";
		s_mapHLSLCommands[Z_FragColor] = "SV_TARGET";
		s_mapHLSLCommands[Z_FragData] = "SV_TARGET";
		s_mapHLSLCommands[Z_FragCoord] = "SV_POSITION";
		s_mapHLSLCommands[Z_FrontFacing] = "SV_ISFRONTFACE";
		s_mapHLSLCommands[Z_PointCoord] = "SV_POSITION";
		s_mapHLSLCommands[Z_FragDepth] = "SV_DEPTH";

		s_mapHLSLLayouts[POSITION] = "POSITION";
		s_mapHLSLLayouts[COLOR] = "COLOR";
		s_mapHLSLLayouts[TEXCOORD] = "TEXCOORD";
		s_mapHLSLLayouts[NORMAL] = "NORMAL";
		s_mapHLSLLayouts[BINORMAL] = "BINORMAL";
		s_mapHLSLLayouts[BLENDWEIGHT] = "BLENDWEIGHT";
		s_mapHLSLLayouts[BLENDINDICES] = "BLENDINDICES";
		s_mapHLSLLayouts[POSITIONT] = "POSITIONT";
		s_mapHLSLLayouts[TANGENT] = "TANGENT";
		s_mapHLSLLayouts[FOG] = "FOG";
		s_mapHLSLLayouts[VFACE] = "VFACE";
		s_mapHLSLLayouts[SEM_NONE] = "";
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
		s_mapSyntaxNames["equal"] = EQUAL;
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

		int bracket_stack = 0;

		if (!token_is(token_t::e_lcrlbracket, e_hold))
			return false;

		for (; ; )
		{
			body_end = current_token().position;

			if (token_is(token_t::e_lcrlbracket))
				bracket_stack++;
			else if (token_is(token_t::e_rcrlbracket))
			{
				if (0 == --bracket_stack)
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

		fd.body = func_def.substr(body_begin, size);

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
		case Uniform:
		{
			if (!token_is_then_assign(token_t::e_symbol, fd.command))
				return false;
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
				if (!token_is_then_assign(token_t::e_number, fd.index))
				{
					return false;
				}
				else {
					fd.isarray = true;
					printf("ARRAY FOUND: %s count %s \n", fd.varname.c_str(), fd.index.c_str());
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

			printf("FUNCTION FOUND: %s\n", current_token().value.c_str());
			std::size_t body_begin = current_token().position;




			printf("Remaining size: %d Index %d \n", var_def.length(), body_begin);
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




		printf("Remaining size: %d Index %d \n", var_def.length(), body_begin);
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
			printf("Command: %s begin %s \n", fd.command.c_str(), fd.begin.c_str());
			switch (parser->s_mapStringCommands[fd.command])
			{
			case Z_Return:
			{
				printf("is Z Return \n");
				next_token();
				if (!token_is(token_t::e_lbracket))
					return false;
				printf("Left Bracket \n");
				if (!token_is_then_assign(token_t::e_symbol, fd.varname))
					return false;
				printf("Command: %s var %s \n", fd.command.c_str(), fd.varname.c_str());
				if (!token_is(token_t::e_rbracket))
					return false;
				if (!token_is(token_t::e_eof))
					return false;
				fd.end = std::to_string(var_def.size() - current_token().position);
				printf("Command: %s end %d \n", fd.command.c_str(), fd.end.c_str());
				break;
			}
			case Texture:
			{	
				size_t bodybegin = 0;
				size_t bodyend = 0;
				 
				bodybegin = current_token().position;
				
				next_token();

				if (!token_is(token_t::e_lbracket))
					return false;
				
				do {
					ZLSLDeclaredVariables vars;
					vars.varname = current_token().value;
					fd.var_list.push_back(vars);
					printf("Token: %s  \n", current_token().value.c_str());
					next_token();
				} while (current_token().type!=token_t::e_eof);
				
				bodyend = current_token().position+1;
				fd.end = std::to_string(bodyend);
				fd.original = var_def.substr(bodybegin, bodyend - bodybegin);

				break;
			}

			}


		}
		else if (parser->s_mapStringVariables[current_token().value] != VAR_NONE) {
			printf("Variable Declare: %s\n", current_token().value.c_str());

			fd.vartype = current_token().value;

			if (token_is(token_t::e_lbracket))
			{
				fd.vartype = "";
			}
			else if (token_is(token_t::e_lsqrbracket))
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
				return false;



		}
		else if (parser->s_mapSyntaxNames[current_token().value] != SYNTAX_NONE) {
			printf("Syntax: %s\n", current_token().value.c_str());

			fd.syntax = current_token().value;

		}
		else if (current_token().type == lexertk::parser_helper::token_t::e_symbol) {
			std::string v = current_token().value;
			fd.varname = parser->IsDeclaredVar(v);


			//fd.varname = current_token().value
		}
		next_token();


		std::size_t body_begin = current_token().position;
		printf("Remaining size: %d Index %d \n", var_def.length(), body_begin);
		if (body_begin < var_def.length())
			var_def = var_def.substr(body_begin, var_def.length() - body_begin);
		else
			var_def = "";


		return true;
	}
}