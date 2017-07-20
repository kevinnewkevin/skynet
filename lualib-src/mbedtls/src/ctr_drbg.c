<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" ToolsVersion="12.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|Win32">
      <Configuration>Debug</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|Win32">
      <Configuration>Release</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <ProjectGuid>{2FF46585-569F-4371-85EE-55E41FD38E8B}</ProjectGuid>
    <Keyword>Win32Proj</Keyword>
    <RootNamespace>lua53</RootNamespace>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v120</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v120</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <LinkIncremental>true</LinkIncremental>
    <IntDir>..\output\$(ProjectName)\$(Configuration)\</IntDir>
    <OutDir>$(SolutionDir)..\..\</OutDir>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <LinkIncremental>false</LinkIncremental>
    <IntDir>..\output\$(ProjectName)\$(Configuration)\</IntDir>
    <OutDir>$(SolutionDir)..\..\</OutDir>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <PreprocessorDefinitions>WIN32;LUA_BUILD_AS_DLL;_DEBUG;_WINDOWS;_USRDLL;LUA53_EXPORTS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <SDLCheck>true</SDLCheck>
      <AdditionalIncludeDirectories>..\..\..\skynet-src;..\posix</AdditionalIncludeDirectories>
    </ClCompile>
    <Link>
      <SubSystem>Windows</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalLibraryDirectories>$(SolutionDir);$(SolutionDir)..\..\</AdditionalLibraryDirectories>
      <AdditionalDependencies>%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <Optimization>MaxSpeed</Optimization>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <PreprocessorDefinitions>WIN32;LUA_BUILD_AS_DLL;NDEBUG;_WINDOWS;_USRDLL;LUA53_EXPORTS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <SDLCheck>true</SDLCheck>
      <AdditionalIncludeDirectories>..\..\..\skynet-src;..\posix</AdditionalIncludeDirectories>
    </ClCompile>
    <Link>
      <SubSystem>Windows</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <AdditionalLibraryDirectories>$(SolutionDir);$(SolutionDir)..\..\</AdditionalLibraryDirectories>
      <AdditionalDependencies>%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ClCompile Include="..\..\..\3rd\lua\lapi.c" />
    <ClCompile Include="..\..\..\3rd\lua\lauxlib.c" />
    <ClCompile Include="..\..\..\3rd\lua\lbaselib.c" />
    <ClCompile Include="..\..\..\3rd\lua\lbitlib.c" />
    <ClCompile Include="..\..\..\3rd\lua\lcode.c" />
    <ClCompile Include="..\..\..\3rd\lua\lcorolib.c" />
    <ClCompile Include="..\..\..\3rd\lua\lctype.c" />
    <ClCompile Include="..\..\..\3rd\lua\ldblib.c" />
    <ClCompile Include="..\..\..\3rd\lua\ldebug.c" />
    <ClCompile Include="..\..\..\3rd\lua\ldo.c" />
    <ClCompile Include="..\..\..\3rd\lua\ldump.c" />
    <ClCompile Include="..\..\..\3rd\lua\lfunc.c" />
    <ClCompile Include="..\..\..\3rd\lua\lgc.c" />
    <ClCompile Include="..\..\..\3rd\lua\linit.c" />
    <ClCompile Include="..\..\..\3rd\lua\liolib.c" />
    <ClCompile Include="..\..\..\3rd\lua\llex.c" />
    <ClCompile Include="..\..\..\3rd\lua\lmathlib.