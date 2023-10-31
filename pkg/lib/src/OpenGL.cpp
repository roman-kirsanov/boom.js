#include <cassert>
#include <iostream>
#include "OpenGL.hpp"

namespace boom {

/* #region OpenGL functions */
boom::GLCullFace glCullFace = nullptr;
boom::GLFrontFace glFrontFace = nullptr;
boom::GLHint glHint = nullptr;
boom::GLLineWidth glLineWidth = nullptr;
boom::GLPointSize glPointSize = nullptr;
boom::GLPolygonMode glPolygonMode = nullptr;
boom::GLScissor glScissor = nullptr;
boom::GLTexParameterf glTexParameterf = nullptr;
boom::GLTexParameterfv glTexParameterfv = nullptr;
boom::GLTexParameteri glTexParameteri = nullptr;
boom::GLTexParameteriv glTexParameteriv = nullptr;
boom::GLTexImage1D glTexImage1D = nullptr;
boom::GLTexImage2D glTexImage2D = nullptr;
boom::GLDrawBuffer glDrawBuffer = nullptr;
boom::GLClear glClear = nullptr;
boom::GLClearColor glClearColor = nullptr;
boom::GLClearStencil glClearStencil = nullptr;
boom::GLClearDepth glClearDepth = nullptr;
boom::GLStencilMask glStencilMask = nullptr;
boom::GLColorMask glColorMask = nullptr;
boom::GLDepthMask glDepthMask = nullptr;
boom::GLDisable glDisable = nullptr;
boom::GLEnable glEnable = nullptr;
boom::GLFinish glFinish = nullptr;
boom::GLFlush glFlush = nullptr;
boom::GLBlendFunc glBlendFunc = nullptr;
boom::GLLogicOp glLogicOp = nullptr;
boom::GLStencilFunc glStencilFunc = nullptr;
boom::GLStencilOp glStencilOp = nullptr;
boom::GLDepthFunc glDepthFunc = nullptr;
boom::GLPixelStoref glPixelStoref = nullptr;
boom::GLPixelStorei glPixelStorei = nullptr;
boom::GLReadBuffer glReadBuffer = nullptr;
boom::GLReadPixels glReadPixels = nullptr;
boom::GLGetBooleanv glGetBooleanv = nullptr;
boom::GLGetDoublev glGetDoublev = nullptr;
boom::GLGetFloatv glGetFloatv = nullptr;
boom::GLGetIntegerv glGetIntegerv = nullptr;
boom::GLGetTexImage glGetTexImage = nullptr;
boom::GLGetTexParameterfv glGetTexParameterfv = nullptr;
boom::GLGetTexParameteriv glGetTexParameteriv = nullptr;
boom::GLGetTexLevelParameterfv glGetTexLevelParameterfv = nullptr;
boom::GLGetTexLevelParameteriv glGetTexLevelParameteriv = nullptr;
boom::GLDepthRange glDepthRange = nullptr;
boom::GLViewport glViewport = nullptr;
boom::GLDrawArrays glDrawArrays = nullptr;
boom::GLDrawElements glDrawElements = nullptr;
boom::GLPolygonOffset glPolygonOffset = nullptr;
boom::GLCopyTexImage1D glCopyTexImage1D = nullptr;
boom::GLCopyTexImage2D glCopyTexImage2D = nullptr;
boom::GLCopyTexSubImage1D glCopyTexSubImage1D = nullptr;
boom::GLCopyTexSubImage2D glCopyTexSubImage2D = nullptr;
boom::GLTexSubImage1D glTexSubImage1D = nullptr;
boom::GLTexSubImage2D glTexSubImage2D = nullptr;
boom::GLBindTexture glBindTexture = nullptr;
boom::GLDeleteTextures glDeleteTextures = nullptr;
boom::GLGenTextures glGenTextures = nullptr;
boom::GLDrawRangeElements glDrawRangeElements = nullptr;
boom::GLTexImage3D glTexImage3D = nullptr;
boom::GLTexSubImage3D glTexSubImage3D = nullptr;
boom::GLCopyTexSubImage3D glCopyTexSubImage3D = nullptr;
boom::GLActiveTexture glActiveTexture = nullptr;
boom::GLSampleCoverage glSampleCoverage = nullptr;
boom::GLCompressedTexImage3D glCompressedTexImage3D = nullptr;
boom::GLCompressedTexImage2D glCompressedTexImage2D = nullptr;
boom::GLCompressedTexImage1D glCompressedTexImage1D = nullptr;
boom::GLCompressedTexSubImage3D glCompressedTexSubImage3D = nullptr;
boom::GLCompressedTexSubImage2D glCompressedTexSubImage2D = nullptr;
boom::GLCompressedTexSubImage1D glCompressedTexSubImage1D = nullptr;
boom::GLGetCompressedTexImage glGetCompressedTexImage = nullptr;
boom::GLBlendFuncSeparate glBlendFuncSeparate = nullptr;
boom::GLMultiDrawArrays glMultiDrawArrays = nullptr;
boom::GLMultiDrawElements glMultiDrawElements = nullptr;
boom::GLPointParameterf glPointParameterf = nullptr;
boom::GLPointParameterfv glPointParameterfv = nullptr;
boom::GLPointParameteri glPointParameteri = nullptr;
boom::GLPointParameteriv glPointParameteriv = nullptr;
boom::GLBlendColor glBlendColor = nullptr;
boom::GLBlendEquation glBlendEquation = nullptr;
boom::GLGenQueries glGenQueries = nullptr;
boom::GLDeleteQueries glDeleteQueries = nullptr;
boom::GLBeginQuery glBeginQuery = nullptr;
boom::GLEndQuery glEndQuery = nullptr;
boom::GLGetQueryiv glGetQueryiv = nullptr;
boom::GLGetQueryObjectiv glGetQueryObjectiv = nullptr;
boom::GLGetQueryObjectuiv glGetQueryObjectuiv = nullptr;
boom::GLBindBuffer glBindBuffer = nullptr;
boom::GLDeleteBuffers glDeleteBuffers = nullptr;
boom::GLGenBuffers glGenBuffers = nullptr;
boom::GLBufferData glBufferData = nullptr;
boom::GLBufferSubData glBufferSubData = nullptr;
boom::GLGetBufferSubData glGetBufferSubData = nullptr;
boom::GLGetBufferParameteriv glGetBufferParameteriv = nullptr;
boom::GLGetBufferPointerv glGetBufferPointerv = nullptr;
boom::GLBlendEquationSeparate glBlendEquationSeparate = nullptr;
boom::GLDrawBuffers glDrawBuffers = nullptr;
boom::GLStencilOpSeparate glStencilOpSeparate = nullptr;
boom::GLStencilFuncSeparate glStencilFuncSeparate = nullptr;
boom::GLStencilMaskSeparate glStencilMaskSeparate = nullptr;
boom::GLAttachShader glAttachShader = nullptr;
boom::GLBindAttribLocation glBindAttribLocation = nullptr;
boom::GLCompileShader glCompileShader = nullptr;
boom::GLDeleteProgram glDeleteProgram = nullptr;
boom::GLDeleteShader glDeleteShader = nullptr;
boom::GLDetachShader glDetachShader = nullptr;
boom::GLDisableVertexAttribArray glDisableVertexAttribArray = nullptr;
boom::GLEnableVertexAttribArray glEnableVertexAttribArray = nullptr;
boom::GLGetActiveAttrib glGetActiveAttrib = nullptr;
boom::GLGetActiveUniform glGetActiveUniform = nullptr;
boom::GLGetAttachedShaders glGetAttachedShaders = nullptr;
boom::GLGetProgramiv glGetProgramiv = nullptr;
boom::GLGetProgramInfoLog glGetProgramInfoLog = nullptr;
boom::GLGetShaderiv glGetShaderiv = nullptr;
boom::GLGetShaderInfoLog glGetShaderInfoLog = nullptr;
boom::GLGetShaderSource glGetShaderSource = nullptr;
boom::GLGetUniformfv glGetUniformfv = nullptr;
boom::GLGetUniformiv glGetUniformiv = nullptr;
boom::GLGetVertexAttribdv glGetVertexAttribdv = nullptr;
boom::GLGetVertexAttribfv glGetVertexAttribfv = nullptr;
boom::GLGetVertexAttribiv glGetVertexAttribiv = nullptr;
boom::GLGetVertexAttribPointerv glGetVertexAttribPointerv = nullptr;
boom::GLLinkProgram glLinkProgram = nullptr;
boom::GLShaderSource glShaderSource = nullptr;
boom::GLUseProgram glUseProgram = nullptr;
boom::GLUniform1f glUniform1f = nullptr;
boom::GLUniform2f glUniform2f = nullptr;
boom::GLUniform3f glUniform3f = nullptr;
boom::GLUniform4f glUniform4f = nullptr;
boom::GLUniform1i glUniform1i = nullptr;
boom::GLUniform2i glUniform2i = nullptr;
boom::GLUniform3i glUniform3i = nullptr;
boom::GLUniform4i glUniform4i = nullptr;
boom::GLUniform1fv glUniform1fv = nullptr;
boom::GLUniform2fv glUniform2fv = nullptr;
boom::GLUniform3fv glUniform3fv = nullptr;
boom::GLUniform4fv glUniform4fv = nullptr;
boom::GLUniform1iv glUniform1iv = nullptr;
boom::GLUniform2iv glUniform2iv = nullptr;
boom::GLUniform3iv glUniform3iv = nullptr;
boom::GLUniform4iv glUniform4iv = nullptr;
boom::GLUniformMatrix2fv glUniformMatrix2fv = nullptr;
boom::GLUniformMatrix3fv glUniformMatrix3fv = nullptr;
boom::GLUniformMatrix4fv glUniformMatrix4fv = nullptr;
boom::GLValidateProgram glValidateProgram = nullptr;
boom::GLVertexAttrib1d glVertexAttrib1d = nullptr;
boom::GLVertexAttrib1dv glVertexAttrib1dv = nullptr;
boom::GLVertexAttrib1f glVertexAttrib1f = nullptr;
boom::GLVertexAttrib1fv glVertexAttrib1fv = nullptr;
boom::GLVertexAttrib1s glVertexAttrib1s = nullptr;
boom::GLVertexAttrib1sv glVertexAttrib1sv = nullptr;
boom::GLVertexAttrib2d glVertexAttrib2d = nullptr;
boom::GLVertexAttrib2dv glVertexAttrib2dv = nullptr;
boom::GLVertexAttrib2f glVertexAttrib2f = nullptr;
boom::GLVertexAttrib2fv glVertexAttrib2fv = nullptr;
boom::GLVertexAttrib2s glVertexAttrib2s = nullptr;
boom::GLVertexAttrib2sv glVertexAttrib2sv = nullptr;
boom::GLVertexAttrib3d glVertexAttrib3d = nullptr;
boom::GLVertexAttrib3dv glVertexAttrib3dv = nullptr;
boom::GLVertexAttrib3f glVertexAttrib3f = nullptr;
boom::GLVertexAttrib3fv glVertexAttrib3fv = nullptr;
boom::GLVertexAttrib3s glVertexAttrib3s = nullptr;
boom::GLVertexAttrib3sv glVertexAttrib3sv = nullptr;
boom::GLVertexAttrib4Nbv glVertexAttrib4Nbv = nullptr;
boom::GLVertexAttrib4Niv glVertexAttrib4Niv = nullptr;
boom::GLVertexAttrib4Nsv glVertexAttrib4Nsv = nullptr;
boom::GLVertexAttrib4Nub glVertexAttrib4Nub = nullptr;
boom::GLVertexAttrib4Nubv glVertexAttrib4Nubv = nullptr;
boom::GLVertexAttrib4Nuiv glVertexAttrib4Nuiv = nullptr;
boom::GLVertexAttrib4Nusv glVertexAttrib4Nusv = nullptr;
boom::GLVertexAttrib4bv glVertexAttrib4bv = nullptr;
boom::GLVertexAttrib4d glVertexAttrib4d = nullptr;
boom::GLVertexAttrib4dv glVertexAttrib4dv = nullptr;
boom::GLVertexAttrib4f glVertexAttrib4f = nullptr;
boom::GLVertexAttrib4fv glVertexAttrib4fv = nullptr;
boom::GLVertexAttrib4iv glVertexAttrib4iv = nullptr;
boom::GLVertexAttrib4s glVertexAttrib4s = nullptr;
boom::GLVertexAttrib4sv glVertexAttrib4sv = nullptr;
boom::GLVertexAttrib4ubv glVertexAttrib4ubv = nullptr;
boom::GLVertexAttrib4uiv glVertexAttrib4uiv = nullptr;
boom::GLVertexAttrib4usv glVertexAttrib4usv = nullptr;
boom::GLVertexAttribPointer glVertexAttribPointer = nullptr;
boom::GLUniformMatrix2x3fv glUniformMatrix2x3fv = nullptr;
boom::GLUniformMatrix3x2fv glUniformMatrix3x2fv = nullptr;
boom::GLUniformMatrix2x4fv glUniformMatrix2x4fv = nullptr;
boom::GLUniformMatrix4x2fv glUniformMatrix4x2fv = nullptr;
boom::GLUniformMatrix3x4fv glUniformMatrix3x4fv = nullptr;
boom::GLUniformMatrix4x3fv glUniformMatrix4x3fv = nullptr;
boom::GLColorMaski glColorMaski = nullptr;
boom::GLGetBooleani_v glGetBooleani_v = nullptr;
boom::GLGetIntegeri_v glGetIntegeri_v = nullptr;
boom::GLEnablei glEnablei = nullptr;
boom::GLDisablei glDisablei = nullptr;
boom::GLBeginTransformFeedback glBeginTransformFeedback = nullptr;
boom::GLEndTransformFeedback glEndTransformFeedback = nullptr;
boom::GLBindBufferRange glBindBufferRange = nullptr;
boom::GLBindBufferBase glBindBufferBase = nullptr;
boom::GLTransformFeedbackVaryings glTransformFeedbackVaryings = nullptr;
boom::GLGetTransformFeedbackVarying glGetTransformFeedbackVarying = nullptr;
boom::GLClampColor glClampColor = nullptr;
boom::GLBeginConditionalRender glBeginConditionalRender = nullptr;
boom::GLEndConditionalRender glEndConditionalRender = nullptr;
boom::GLVertexAttribIPointer glVertexAttribIPointer = nullptr;
boom::GLGetVertexAttribIiv glGetVertexAttribIiv = nullptr;
boom::GLGetVertexAttribIuiv glGetVertexAttribIuiv = nullptr;
boom::GLVertexAttribI1i glVertexAttribI1i = nullptr;
boom::GLVertexAttribI2i glVertexAttribI2i = nullptr;
boom::GLVertexAttribI3i glVertexAttribI3i = nullptr;
boom::GLVertexAttribI4i glVertexAttribI4i = nullptr;
boom::GLVertexAttribI1ui glVertexAttribI1ui = nullptr;
boom::GLVertexAttribI2ui glVertexAttribI2ui = nullptr;
boom::GLVertexAttribI3ui glVertexAttribI3ui = nullptr;
boom::GLVertexAttribI4ui glVertexAttribI4ui = nullptr;
boom::GLVertexAttribI1iv glVertexAttribI1iv = nullptr;
boom::GLVertexAttribI2iv glVertexAttribI2iv = nullptr;
boom::GLVertexAttribI3iv glVertexAttribI3iv = nullptr;
boom::GLVertexAttribI4iv glVertexAttribI4iv = nullptr;
boom::GLVertexAttribI1uiv glVertexAttribI1uiv = nullptr;
boom::GLVertexAttribI2uiv glVertexAttribI2uiv = nullptr;
boom::GLVertexAttribI3uiv glVertexAttribI3uiv = nullptr;
boom::GLVertexAttribI4uiv glVertexAttribI4uiv = nullptr;
boom::GLVertexAttribI4bv glVertexAttribI4bv = nullptr;
boom::GLVertexAttribI4sv glVertexAttribI4sv = nullptr;
boom::GLVertexAttribI4ubv glVertexAttribI4ubv = nullptr;
boom::GLVertexAttribI4usv glVertexAttribI4usv = nullptr;
boom::GLGetUniformuiv glGetUniformuiv = nullptr;
boom::GLBindFragDataLocation glBindFragDataLocation = nullptr;
boom::GLUniform1ui glUniform1ui = nullptr;
boom::GLUniform2ui glUniform2ui = nullptr;
boom::GLUniform3ui glUniform3ui = nullptr;
boom::GLUniform4ui glUniform4ui = nullptr;
boom::GLUniform1uiv glUniform1uiv = nullptr;
boom::GLUniform2uiv glUniform2uiv = nullptr;
boom::GLUniform3uiv glUniform3uiv = nullptr;
boom::GLUniform4uiv glUniform4uiv = nullptr;
boom::GLTexParameterIiv glTexParameterIiv = nullptr;
boom::GLTexParameterIuiv glTexParameterIuiv = nullptr;
boom::GLGetTexParameterIiv glGetTexParameterIiv = nullptr;
boom::GLGetTexParameterIuiv glGetTexParameterIuiv = nullptr;
boom::GLClearBufferiv glClearBufferiv = nullptr;
boom::GLClearBufferuiv glClearBufferuiv = nullptr;
boom::GLClearBufferfv glClearBufferfv = nullptr;
boom::GLClearBufferfi glClearBufferfi = nullptr;
boom::GLBindRenderbuffer glBindRenderbuffer = nullptr;
boom::GLDeleteRenderbuffers glDeleteRenderbuffers = nullptr;
boom::GLGenRenderbuffers glGenRenderbuffers = nullptr;
boom::GLRenderbufferStorage glRenderbufferStorage = nullptr;
boom::GLGetRenderbufferParameteriv glGetRenderbufferParameteriv = nullptr;
boom::GLBindFramebuffer glBindFramebuffer = nullptr;
boom::GLDeleteFramebuffers glDeleteFramebuffers = nullptr;
boom::GLGenFramebuffers glGenFramebuffers = nullptr;
boom::GLFramebufferTexture1D glFramebufferTexture1D = nullptr;
boom::GLFramebufferTexture2D glFramebufferTexture2D = nullptr;
boom::GLFramebufferTexture3D glFramebufferTexture3D = nullptr;
boom::GLFramebufferRenderbuffer glFramebufferRenderbuffer = nullptr;
boom::GLGetFramebufferAttachmentParameteriv glGetFramebufferAttachmentParameteriv = nullptr;
boom::GLGenerateMipmap glGenerateMipmap = nullptr;
boom::GLBlitFramebuffer glBlitFramebuffer = nullptr;
boom::GLRenderbufferStorageMultisample glRenderbufferStorageMultisample = nullptr;
boom::GLFramebufferTextureLayer glFramebufferTextureLayer = nullptr;
boom::GLFlushMappedBufferRange glFlushMappedBufferRange = nullptr;
boom::GLBindVertexArray glBindVertexArray = nullptr;
boom::GLDeleteVertexArrays glDeleteVertexArrays = nullptr;
boom::GLGenVertexArrays glGenVertexArrays = nullptr;
boom::GLDrawArraysInstanced glDrawArraysInstanced = nullptr;
boom::GLDrawElementsInstanced glDrawElementsInstanced = nullptr;
boom::GLTexBuffer glTexBuffer = nullptr;
boom::GLPrimitiveRestartIndex glPrimitiveRestartIndex = nullptr;
boom::GLCopyBufferSubData glCopyBufferSubData = nullptr;
boom::GLGetUniformIndices glGetUniformIndices = nullptr;
boom::GLGetActiveUniformsiv glGetActiveUniformsiv = nullptr;
boom::GLGetActiveUniformName glGetActiveUniformName = nullptr;
boom::GLGetActiveUniformBlockiv glGetActiveUniformBlockiv = nullptr;
boom::GLGetActiveUniformBlockName glGetActiveUniformBlockName = nullptr;
boom::GLUniformBlockBinding glUniformBlockBinding = nullptr;
boom::GLDrawElementsBaseVertex glDrawElementsBaseVertex = nullptr;
boom::GLDrawRangeElementsBaseVertex glDrawRangeElementsBaseVertex = nullptr;
boom::GLDrawElementsInstancedBaseVertex glDrawElementsInstancedBaseVertex = nullptr;
boom::GLMultiDrawElementsBaseVertex glMultiDrawElementsBaseVertex = nullptr;
boom::GLProvokingVertex glProvokingVertex = nullptr;
boom::GLDeleteSync glDeleteSync = nullptr;
boom::GLWaitSync glWaitSync = nullptr;
boom::GLGetInteger64v glGetInteger64v = nullptr;
boom::GLGetSynciv glGetSynciv = nullptr;
boom::GLGetInteger64i_v glGetInteger64i_v = nullptr;
boom::GLGetBufferParameteri64v glGetBufferParameteri64v = nullptr;
boom::GLFramebufferTexture glFramebufferTexture = nullptr;
boom::GLTexImage2DMultisample glTexImage2DMultisample = nullptr;
boom::GLTexImage3DMultisample glTexImage3DMultisample = nullptr;
boom::GLGetMultisamplefv glGetMultisamplefv = nullptr;
boom::GLSampleMaski glSampleMaski = nullptr;
boom::GLBindFragDataLocationIndexed glBindFragDataLocationIndexed = nullptr;
boom::GLGenSamplers glGenSamplers = nullptr;
boom::GLDeleteSamplers glDeleteSamplers = nullptr;
boom::GLBindSampler glBindSampler = nullptr;
boom::GLSamplerParameteri glSamplerParameteri = nullptr;
boom::GLSamplerParameteriv glSamplerParameteriv = nullptr;
boom::GLSamplerParameterf glSamplerParameterf = nullptr;
boom::GLSamplerParameterfv glSamplerParameterfv = nullptr;
boom::GLSamplerParameterIiv glSamplerParameterIiv = nullptr;
boom::GLSamplerParameterIuiv glSamplerParameterIuiv = nullptr;
boom::GLGetSamplerParameteriv glGetSamplerParameteriv = nullptr;
boom::GLGetSamplerParameterIiv glGetSamplerParameterIiv = nullptr;
boom::GLGetSamplerParameterfv glGetSamplerParameterfv = nullptr;
boom::GLGetSamplerParameterIuiv glGetSamplerParameterIuiv = nullptr;
boom::GLQueryCounter glQueryCounter = nullptr;
boom::GLGetQueryObjecti64v glGetQueryObjecti64v = nullptr;
boom::GLGetQueryObjectui64v glGetQueryObjectui64v = nullptr;
boom::GLVertexAttribDivisor glVertexAttribDivisor = nullptr;
boom::GLVertexAttribP1ui glVertexAttribP1ui = nullptr;
boom::GLVertexAttribP1uiv glVertexAttribP1uiv = nullptr;
boom::GLVertexAttribP2ui glVertexAttribP2ui = nullptr;
boom::GLVertexAttribP2uiv glVertexAttribP2uiv = nullptr;
boom::GLVertexAttribP3ui glVertexAttribP3ui = nullptr;
boom::GLVertexAttribP3uiv glVertexAttribP3uiv = nullptr;
boom::GLVertexAttribP4ui glVertexAttribP4ui = nullptr;
boom::GLVertexAttribP4uiv glVertexAttribP4uiv = nullptr;
boom::GLVertexP2ui glVertexP2ui = nullptr;
boom::GLVertexP2uiv glVertexP2uiv = nullptr;
boom::GLVertexP3ui glVertexP3ui = nullptr;
boom::GLVertexP3uiv glVertexP3uiv = nullptr;
boom::GLVertexP4ui glVertexP4ui = nullptr;
boom::GLVertexP4uiv glVertexP4uiv = nullptr;
boom::GLTexCoordP1ui glTexCoordP1ui = nullptr;
boom::GLTexCoordP1uiv glTexCoordP1uiv = nullptr;
boom::GLTexCoordP2ui glTexCoordP2ui = nullptr;
boom::GLTexCoordP2uiv glTexCoordP2uiv = nullptr;
boom::GLTexCoordP3ui glTexCoordP3ui = nullptr;
boom::GLTexCoordP3uiv glTexCoordP3uiv = nullptr;
boom::GLTexCoordP4ui glTexCoordP4ui = nullptr;
boom::GLTexCoordP4uiv glTexCoordP4uiv = nullptr;
boom::GLMultiTexCoordP1ui glMultiTexCoordP1ui = nullptr;
boom::GLMultiTexCoordP1uiv glMultiTexCoordP1uiv = nullptr;
boom::GLMultiTexCoordP2ui glMultiTexCoordP2ui = nullptr;
boom::GLMultiTexCoordP2uiv glMultiTexCoordP2uiv = nullptr;
boom::GLMultiTexCoordP3ui glMultiTexCoordP3ui = nullptr;
boom::GLMultiTexCoordP3uiv glMultiTexCoordP3uiv = nullptr;
boom::GLMultiTexCoordP4ui glMultiTexCoordP4ui = nullptr;
boom::GLMultiTexCoordP4uiv glMultiTexCoordP4uiv = nullptr;
boom::GLNormalP3ui glNormalP3ui = nullptr;
boom::GLNormalP3uiv glNormalP3uiv = nullptr;
boom::GLColorP3ui glColorP3ui = nullptr;
boom::GLColorP3uiv glColorP3uiv = nullptr;
boom::GLColorP4ui glColorP4ui = nullptr;
boom::GLColorP4uiv glColorP4uiv = nullptr;
boom::GLSecondaryColorP3ui glSecondaryColorP3ui = nullptr;
boom::GLSecondaryColorP3uiv glSecondaryColorP3uiv = nullptr;
boom::GLMinSampleShading glMinSampleShading = nullptr;
boom::GLBlendEquationi glBlendEquationi = nullptr;
boom::GLBlendEquationSeparatei glBlendEquationSeparatei = nullptr;
boom::GLBlendFunci glBlendFunci = nullptr;
boom::GLBlendFuncSeparatei glBlendFuncSeparatei = nullptr;
boom::GLDrawArraysIndirect glDrawArraysIndirect = nullptr;
boom::GLDrawElementsIndirect glDrawElementsIndirect = nullptr;
boom::GLUniform1d glUniform1d = nullptr;
boom::GLUniform2d glUniform2d = nullptr;
boom::GLUniform3d glUniform3d = nullptr;
boom::GLUniform4d glUniform4d = nullptr;
boom::GLUniform1dv glUniform1dv = nullptr;
boom::GLUniform2dv glUniform2dv = nullptr;
boom::GLUniform3dv glUniform3dv = nullptr;
boom::GLUniform4dv glUniform4dv = nullptr;
boom::GLUniformMatrix2dv glUniformMatrix2dv = nullptr;
boom::GLUniformMatrix3dv glUniformMatrix3dv = nullptr;
boom::GLUniformMatrix4dv glUniformMatrix4dv = nullptr;
boom::GLUniformMatrix2x3dv glUniformMatrix2x3dv = nullptr;
boom::GLUniformMatrix2x4dv glUniformMatrix2x4dv = nullptr;
boom::GLUniformMatrix3x2dv glUniformMatrix3x2dv = nullptr;
boom::GLUniformMatrix3x4dv glUniformMatrix3x4dv = nullptr;
boom::GLUniformMatrix4x2dv glUniformMatrix4x2dv = nullptr;
boom::GLUniformMatrix4x3dv glUniformMatrix4x3dv = nullptr;
boom::GLGetUniformdv glGetUniformdv = nullptr;
boom::GLGetActiveSubroutineUniformiv glGetActiveSubroutineUniformiv = nullptr;
boom::GLGetActiveSubroutineUniformName glGetActiveSubroutineUniformName = nullptr;
boom::GLGetActiveSubroutineName glGetActiveSubroutineName = nullptr;
boom::GLUniformSubroutinesuiv glUniformSubroutinesuiv = nullptr;
boom::GLGetUniformSubroutineuiv glGetUniformSubroutineuiv = nullptr;
boom::GLGetProgramStageiv glGetProgramStageiv = nullptr;
boom::GLPatchParameteri glPatchParameteri = nullptr;
boom::GLPatchParameterfv glPatchParameterfv = nullptr;
boom::GLBindTransformFeedback glBindTransformFeedback = nullptr;
boom::GLDeleteTransformFeedbacks glDeleteTransformFeedbacks = nullptr;
boom::GLGenTransformFeedbacks glGenTransformFeedbacks = nullptr;
boom::GLPauseTransformFeedback glPauseTransformFeedback = nullptr;
boom::GLResumeTransformFeedback glResumeTransformFeedback = nullptr;
boom::GLDrawTransformFeedback glDrawTransformFeedback = nullptr;
boom::GLDrawTransformFeedbackStream glDrawTransformFeedbackStream = nullptr;
boom::GLBeginQueryIndexed glBeginQueryIndexed = nullptr;
boom::GLEndQueryIndexed glEndQueryIndexed = nullptr;
boom::GLGetQueryIndexediv glGetQueryIndexediv = nullptr;
boom::GLReleaseShaderCompiler glReleaseShaderCompiler = nullptr;
boom::GLShaderBinary glShaderBinary = nullptr;
boom::GLGetShaderPrecisionFormat glGetShaderPrecisionFormat = nullptr;
boom::GLDepthRangef glDepthRangef = nullptr;
boom::GLClearDepthf glClearDepthf = nullptr;
boom::GLGetProgramBinary glGetProgramBinary = nullptr;
boom::GLProgramBinary glProgramBinary = nullptr;
boom::GLProgramParameteri glProgramParameteri = nullptr;
boom::GLUseProgramStages glUseProgramStages = nullptr;
boom::GLActiveShaderProgram glActiveShaderProgram = nullptr;
boom::GLBindProgramPipeline glBindProgramPipeline = nullptr;
boom::GLDeleteProgramPipelines glDeleteProgramPipelines = nullptr;
boom::GLGenProgramPipelines glGenProgramPipelines = nullptr;
boom::GLGetProgramPipelineiv glGetProgramPipelineiv = nullptr;
boom::GLProgramUniform1i glProgramUniform1i = nullptr;
boom::GLProgramUniform1iv glProgramUniform1iv = nullptr;
boom::GLProgramUniform1f glProgramUniform1f = nullptr;
boom::GLProgramUniform1fv glProgramUniform1fv = nullptr;
boom::GLProgramUniform1d glProgramUniform1d = nullptr;
boom::GLProgramUniform1dv glProgramUniform1dv = nullptr;
boom::GLProgramUniform1ui glProgramUniform1ui = nullptr;
boom::GLProgramUniform1uiv glProgramUniform1uiv = nullptr;
boom::GLProgramUniform2i glProgramUniform2i = nullptr;
boom::GLProgramUniform2iv glProgramUniform2iv = nullptr;
boom::GLProgramUniform2f glProgramUniform2f = nullptr;
boom::GLProgramUniform2fv glProgramUniform2fv = nullptr;
boom::GLProgramUniform2d glProgramUniform2d = nullptr;
boom::GLProgramUniform2dv glProgramUniform2dv = nullptr;
boom::GLProgramUniform2ui glProgramUniform2ui = nullptr;
boom::GLProgramUniform2uiv glProgramUniform2uiv = nullptr;
boom::GLProgramUniform3i glProgramUniform3i = nullptr;
boom::GLProgramUniform3iv glProgramUniform3iv = nullptr;
boom::GLProgramUniform3f glProgramUniform3f = nullptr;
boom::GLProgramUniform3fv glProgramUniform3fv = nullptr;
boom::GLProgramUniform3d glProgramUniform3d = nullptr;
boom::GLProgramUniform3dv glProgramUniform3dv = nullptr;
boom::GLProgramUniform3ui glProgramUniform3ui = nullptr;
boom::GLProgramUniform3uiv glProgramUniform3uiv = nullptr;
boom::GLProgramUniform4i glProgramUniform4i = nullptr;
boom::GLProgramUniform4iv glProgramUniform4iv = nullptr;
boom::GLProgramUniform4f glProgramUniform4f = nullptr;
boom::GLProgramUniform4fv glProgramUniform4fv = nullptr;
boom::GLProgramUniform4d glProgramUniform4d = nullptr;
boom::GLProgramUniform4dv glProgramUniform4dv = nullptr;
boom::GLProgramUniform4ui glProgramUniform4ui = nullptr;
boom::GLProgramUniform4uiv glProgramUniform4uiv = nullptr;
boom::GLProgramUniformMatrix2fv glProgramUniformMatrix2fv = nullptr;
boom::GLProgramUniformMatrix3fv glProgramUniformMatrix3fv = nullptr;
boom::GLProgramUniformMatrix4fv glProgramUniformMatrix4fv = nullptr;
boom::GLProgramUniformMatrix2dv glProgramUniformMatrix2dv = nullptr;
boom::GLProgramUniformMatrix3dv glProgramUniformMatrix3dv = nullptr;
boom::GLProgramUniformMatrix4dv glProgramUniformMatrix4dv = nullptr;
boom::GLProgramUniformMatrix2x3fv glProgramUniformMatrix2x3fv = nullptr;
boom::GLProgramUniformMatrix3x2fv glProgramUniformMatrix3x2fv = nullptr;
boom::GLProgramUniformMatrix2x4fv glProgramUniformMatrix2x4fv = nullptr;
boom::GLProgramUniformMatrix4x2fv glProgramUniformMatrix4x2fv = nullptr;
boom::GLProgramUniformMatrix3x4fv glProgramUniformMatrix3x4fv = nullptr;
boom::GLProgramUniformMatrix4x3fv glProgramUniformMatrix4x3fv = nullptr;
boom::GLProgramUniformMatrix2x3dv glProgramUniformMatrix2x3dv = nullptr;
boom::GLProgramUniformMatrix3x2dv glProgramUniformMatrix3x2dv = nullptr;
boom::GLProgramUniformMatrix2x4dv glProgramUniformMatrix2x4dv = nullptr;
boom::GLProgramUniformMatrix4x2dv glProgramUniformMatrix4x2dv = nullptr;
boom::GLProgramUniformMatrix3x4dv glProgramUniformMatrix3x4dv = nullptr;
boom::GLProgramUniformMatrix4x3dv glProgramUniformMatrix4x3dv = nullptr;
boom::GLValidateProgramPipeline glValidateProgramPipeline = nullptr;
boom::GLGetProgramPipelineInfoLog glGetProgramPipelineInfoLog = nullptr;
boom::GLVertexAttribL1d glVertexAttribL1d = nullptr;
boom::GLVertexAttribL2d glVertexAttribL2d = nullptr;
boom::GLVertexAttribL3d glVertexAttribL3d = nullptr;
boom::GLVertexAttribL4d glVertexAttribL4d = nullptr;
boom::GLVertexAttribL1dv glVertexAttribL1dv = nullptr;
boom::GLVertexAttribL2dv glVertexAttribL2dv = nullptr;
boom::GLVertexAttribL3dv glVertexAttribL3dv = nullptr;
boom::GLVertexAttribL4dv glVertexAttribL4dv = nullptr;
boom::GLVertexAttribLPointer glVertexAttribLPointer = nullptr;
boom::GLGetVertexAttribLdv glGetVertexAttribLdv = nullptr;
boom::GLViewportArrayv glViewportArrayv = nullptr;
boom::GLViewportIndexedf glViewportIndexedf = nullptr;
boom::GLViewportIndexedfv glViewportIndexedfv = nullptr;
boom::GLScissorArrayv glScissorArrayv = nullptr;
boom::GLScissorIndexed glScissorIndexed = nullptr;
boom::GLScissorIndexedv glScissorIndexedv = nullptr;
boom::GLDepthRangeArrayv glDepthRangeArrayv = nullptr;
boom::GLDepthRangeIndexed glDepthRangeIndexed = nullptr;
boom::GLGetFloati_v glGetFloati_v = nullptr;
boom::GLGetDoublei_v glGetDoublei_v = nullptr;
boom::GLDrawArraysInstancedBaseInstance glDrawArraysInstancedBaseInstance = nullptr;
boom::GLDrawElementsInstancedBaseInstance glDrawElementsInstancedBaseInstance = nullptr;
boom::GLDrawElementsInstancedBaseVertexBaseInstance glDrawElementsInstancedBaseVertexBaseInstance = nullptr;
boom::GLGetInternalformativ glGetInternalformativ = nullptr;
boom::GLGetActiveAtomicCounterBufferiv glGetActiveAtomicCounterBufferiv = nullptr;
boom::GLBindImageTexture glBindImageTexture = nullptr;
boom::GLMemoryBarrier glMemoryBarrier = nullptr;
boom::GLTexStorage1D glTexStorage1D = nullptr;
boom::GLTexStorage2D glTexStorage2D = nullptr;
boom::GLTexStorage3D glTexStorage3D = nullptr;
boom::GLDrawTransformFeedbackInstanced glDrawTransformFeedbackInstanced = nullptr;
boom::GLDrawTransformFeedbackStreamInstanced glDrawTransformFeedbackStreamInstanced = nullptr;
boom::GLClearBufferData glClearBufferData = nullptr;
boom::GLClearBufferSubData glClearBufferSubData = nullptr;
boom::GLDispatchCompute glDispatchCompute = nullptr;
boom::GLDispatchComputeIndirect glDispatchComputeIndirect = nullptr;
boom::GLCopyImageSubData glCopyImageSubData = nullptr;
boom::GLFramebufferParameteri glFramebufferParameteri = nullptr;
boom::GLGetFramebufferParameteriv glGetFramebufferParameteriv = nullptr;
boom::GLGetInternalformati64v glGetInternalformati64v = nullptr;
boom::GLInvalidateTexSubImage glInvalidateTexSubImage = nullptr;
boom::GLInvalidateTexImage glInvalidateTexImage = nullptr;
boom::GLInvalidateBufferSubData glInvalidateBufferSubData = nullptr;
boom::GLInvalidateBufferData glInvalidateBufferData = nullptr;
boom::GLInvalidateFramebuffer glInvalidateFramebuffer = nullptr;
boom::GLInvalidateSubFramebuffer glInvalidateSubFramebuffer = nullptr;
boom::GLMultiDrawArraysIndirect glMultiDrawArraysIndirect = nullptr;
boom::GLMultiDrawElementsIndirect glMultiDrawElementsIndirect = nullptr;
boom::GLGetProgramInterfaceiv glGetProgramInterfaceiv = nullptr;
boom::GLGetProgramResourceName glGetProgramResourceName = nullptr;
boom::GLGetProgramResourceiv glGetProgramResourceiv = nullptr;
boom::GLShaderStorageBlockBinding glShaderStorageBlockBinding = nullptr;
boom::GLTexBufferRange glTexBufferRange = nullptr;
boom::GLTexStorage2DMultisample glTexStorage2DMultisample = nullptr;
boom::GLTexStorage3DMultisample glTexStorage3DMultisample = nullptr;
boom::GLTextureView glTextureView = nullptr;
boom::GLBindVertexBuffer glBindVertexBuffer = nullptr;
boom::GLVertexAttribFormat glVertexAttribFormat = nullptr;
boom::GLVertexAttribIFormat glVertexAttribIFormat = nullptr;
boom::GLVertexAttribLFormat glVertexAttribLFormat = nullptr;
boom::GLVertexAttribBinding glVertexAttribBinding = nullptr;
boom::GLVertexBindingDivisor glVertexBindingDivisor = nullptr;
boom::GLDebugMessageControl glDebugMessageControl = nullptr;
boom::GLDebugMessageInsert glDebugMessageInsert = nullptr;
boom::GLDebugMessageCallback glDebugMessageCallback = nullptr;
boom::GLPushDebugGroup glPushDebugGroup = nullptr;
boom::GLPopDebugGroup glPopDebugGroup = nullptr;
boom::GLObjectLabel glObjectLabel = nullptr;
boom::GLGetObjectLabel glGetObjectLabel = nullptr;
boom::GLObjectPtrLabel glObjectPtrLabel = nullptr;
boom::GLGetObjectPtrLabel glGetObjectPtrLabel = nullptr;
boom::GLGetPointerv glGetPointerv = nullptr;
boom::GLBufferStorage glBufferStorage = nullptr;
boom::GLClearTexImage glClearTexImage = nullptr;
boom::GLClearTexSubImage glClearTexSubImage = nullptr;
boom::GLBindBuffersBase glBindBuffersBase = nullptr;
boom::GLBindBuffersRange glBindBuffersRange = nullptr;
boom::GLBindTextures glBindTextures = nullptr;
boom::GLBindSamplers glBindSamplers = nullptr;
boom::GLBindImageTextures glBindImageTextures = nullptr;
boom::GLBindVertexBuffers glBindVertexBuffers = nullptr;
boom::GLClipControl glClipControl = nullptr;
boom::GLCreateTransformFeedbacks glCreateTransformFeedbacks = nullptr;
boom::GLTransformFeedbackBufferBase glTransformFeedbackBufferBase = nullptr;
boom::GLTransformFeedbackBufferRange glTransformFeedbackBufferRange = nullptr;
boom::GLGetTransformFeedbackiv glGetTransformFeedbackiv = nullptr;
boom::GLGetTransformFeedbacki_v glGetTransformFeedbacki_v = nullptr;
boom::GLGetTransformFeedbacki64_v glGetTransformFeedbacki64_v = nullptr;
boom::GLCreateBuffers glCreateBuffers = nullptr;
boom::GLNamedBufferStorage glNamedBufferStorage = nullptr;
boom::GLNamedBufferData glNamedBufferData = nullptr;
boom::GLNamedBufferSubData glNamedBufferSubData = nullptr;
boom::GLCopyNamedBufferSubData glCopyNamedBufferSubData = nullptr;
boom::GLClearNamedBufferData glClearNamedBufferData = nullptr;
boom::GLClearNamedBufferSubData glClearNamedBufferSubData = nullptr;
boom::GLFlushMappedNamedBufferRange glFlushMappedNamedBufferRange = nullptr;
boom::GLGetNamedBufferParameteriv glGetNamedBufferParameteriv = nullptr;
boom::GLGetNamedBufferParameteri64v glGetNamedBufferParameteri64v = nullptr;
boom::GLGetNamedBufferPointerv glGetNamedBufferPointerv = nullptr;
boom::GLGetNamedBufferSubData glGetNamedBufferSubData = nullptr;
boom::GLCreateFramebuffers glCreateFramebuffers = nullptr;
boom::GLNamedFramebufferRenderbuffer glNamedFramebufferRenderbuffer = nullptr;
boom::GLNamedFramebufferParameteri glNamedFramebufferParameteri = nullptr;
boom::GLNamedFramebufferTexture glNamedFramebufferTexture = nullptr;
boom::GLNamedFramebufferTextureLayer glNamedFramebufferTextureLayer = nullptr;
boom::GLNamedFramebufferDrawBuffer glNamedFramebufferDrawBuffer = nullptr;
boom::GLNamedFramebufferDrawBuffers glNamedFramebufferDrawBuffers = nullptr;
boom::GLNamedFramebufferReadBuffer glNamedFramebufferReadBuffer = nullptr;
boom::GLInvalidateNamedFramebufferData glInvalidateNamedFramebufferData = nullptr;
boom::GLInvalidateNamedFramebufferSubData glInvalidateNamedFramebufferSubData = nullptr;
boom::GLClearNamedFramebufferiv glClearNamedFramebufferiv = nullptr;
boom::GLClearNamedFramebufferuiv glClearNamedFramebufferuiv = nullptr;
boom::GLClearNamedFramebufferfv glClearNamedFramebufferfv = nullptr;
boom::GLClearNamedFramebufferfi glClearNamedFramebufferfi = nullptr;
boom::GLBlitNamedFramebuffer glBlitNamedFramebuffer = nullptr;
boom::GLGetNamedFramebufferParameteriv glGetNamedFramebufferParameteriv = nullptr;
boom::GLGetNamedFramebufferAttachmentParameteriv glGetNamedFramebufferAttachmentParameteriv = nullptr;
boom::GLCreateRenderbuffers glCreateRenderbuffers = nullptr;
boom::GLNamedRenderbufferStorage glNamedRenderbufferStorage = nullptr;
boom::GLNamedRenderbufferStorageMultisample glNamedRenderbufferStorageMultisample = nullptr;
boom::GLGetNamedRenderbufferParameteriv glGetNamedRenderbufferParameteriv = nullptr;
boom::GLCreateTextures glCreateTextures = nullptr;
boom::GLTextureBuffer glTextureBuffer = nullptr;
boom::GLTextureBufferRange glTextureBufferRange = nullptr;
boom::GLTextureStorage1D glTextureStorage1D = nullptr;
boom::GLTextureStorage2D glTextureStorage2D = nullptr;
boom::GLTextureStorage3D glTextureStorage3D = nullptr;
boom::GLTextureStorage2DMultisample glTextureStorage2DMultisample = nullptr;
boom::GLTextureStorage3DMultisample glTextureStorage3DMultisample = nullptr;
boom::GLTextureSubImage1D glTextureSubImage1D = nullptr;
boom::GLTextureSubImage2D glTextureSubImage2D = nullptr;
boom::GLTextureSubImage3D glTextureSubImage3D = nullptr;
boom::GLCompressedTextureSubImage1D glCompressedTextureSubImage1D = nullptr;
boom::GLCompressedTextureSubImage2D glCompressedTextureSubImage2D = nullptr;
boom::GLCompressedTextureSubImage3D glCompressedTextureSubImage3D = nullptr;
boom::GLCopyTextureSubImage1D glCopyTextureSubImage1D = nullptr;
boom::GLCopyTextureSubImage2D glCopyTextureSubImage2D = nullptr;
boom::GLCopyTextureSubImage3D glCopyTextureSubImage3D = nullptr;
boom::GLTextureParameterf glTextureParameterf = nullptr;
boom::GLTextureParameterfv glTextureParameterfv = nullptr;
boom::GLTextureParameteri glTextureParameteri = nullptr;
boom::GLTextureParameterIiv glTextureParameterIiv = nullptr;
boom::GLTextureParameterIuiv glTextureParameterIuiv = nullptr;
boom::GLTextureParameteriv glTextureParameteriv = nullptr;
boom::GLGenerateTextureMipmap glGenerateTextureMipmap = nullptr;
boom::GLBindTextureUnit glBindTextureUnit = nullptr;
boom::GLGetTextureImage glGetTextureImage = nullptr;
boom::GLGetCompressedTextureImage glGetCompressedTextureImage = nullptr;
boom::GLGetTextureLevelParameterfv glGetTextureLevelParameterfv = nullptr;
boom::GLGetTextureLevelParameteriv glGetTextureLevelParameteriv = nullptr;
boom::GLGetTextureParameterfv glGetTextureParameterfv = nullptr;
boom::GLGetTextureParameterIiv glGetTextureParameterIiv = nullptr;
boom::GLGetTextureParameterIuiv glGetTextureParameterIuiv = nullptr;
boom::GLGetTextureParameteriv glGetTextureParameteriv = nullptr;
boom::GLCreateVertexArrays glCreateVertexArrays = nullptr;
boom::GLDisableVertexArrayAttrib glDisableVertexArrayAttrib = nullptr;
boom::GLEnableVertexArrayAttrib glEnableVertexArrayAttrib = nullptr;
boom::GLVertexArrayElementBuffer glVertexArrayElementBuffer = nullptr;
boom::GLVertexArrayVertexBuffer glVertexArrayVertexBuffer = nullptr;
boom::GLVertexArrayVertexBuffers glVertexArrayVertexBuffers = nullptr;
boom::GLVertexArrayAttribBinding glVertexArrayAttribBinding = nullptr;
boom::GLVertexArrayAttribFormat glVertexArrayAttribFormat = nullptr;
boom::GLVertexArrayAttribIFormat glVertexArrayAttribIFormat = nullptr;
boom::GLVertexArrayAttribLFormat glVertexArrayAttribLFormat = nullptr;
boom::GLVertexArrayBindingDivisor glVertexArrayBindingDivisor = nullptr;
boom::GLGetVertexArrayiv glGetVertexArrayiv = nullptr;
boom::GLGetVertexArrayIndexediv glGetVertexArrayIndexediv = nullptr;
boom::GLGetVertexArrayIndexed64iv glGetVertexArrayIndexed64iv = nullptr;
boom::GLCreateSamplers glCreateSamplers = nullptr;
boom::GLCreateProgramPipelines glCreateProgramPipelines = nullptr;
boom::GLCreateQueries glCreateQueries = nullptr;
boom::GLGetQueryBufferObjecti64v glGetQueryBufferObjecti64v = nullptr;
boom::GLGetQueryBufferObjectiv glGetQueryBufferObjectiv = nullptr;
boom::GLGetQueryBufferObjectui64v glGetQueryBufferObjectui64v = nullptr;
boom::GLGetQueryBufferObjectuiv glGetQueryBufferObjectuiv = nullptr;
boom::GLMemoryBarrierByRegion glMemoryBarrierByRegion = nullptr;
boom::GLGetTextureSubImage glGetTextureSubImage = nullptr;
boom::GLGetCompressedTextureSubImage glGetCompressedTextureSubImage = nullptr;
boom::GLGetnCompressedTexImage glGetnCompressedTexImage = nullptr;
boom::GLGetnTexImage glGetnTexImage = nullptr;
boom::GLGetnUniformdv glGetnUniformdv = nullptr;
boom::GLGetnUniformfv glGetnUniformfv = nullptr;
boom::GLGetnUniformiv glGetnUniformiv = nullptr;
boom::GLGetnUniformuiv glGetnUniformuiv = nullptr;
boom::GLReadnPixels glReadnPixels = nullptr;
boom::GLGetnMapdv glGetnMapdv = nullptr;
boom::GLGetnMapfv glGetnMapfv = nullptr;
boom::GLGetnMapiv glGetnMapiv = nullptr;
boom::GLGetnPixelMapfv glGetnPixelMapfv = nullptr;
boom::GLGetnPixelMapuiv glGetnPixelMapuiv = nullptr;
boom::GLGetnPixelMapusv glGetnPixelMapusv = nullptr;
boom::GLGetnPolygonStipple glGetnPolygonStipple = nullptr;
boom::GLGetnColorTable glGetnColorTable = nullptr;
boom::GLGetnConvolutionFilter glGetnConvolutionFilter = nullptr;
boom::GLGetnSeparableFilter glGetnSeparableFilter = nullptr;
boom::GLGetnHistogram glGetnHistogram = nullptr;
boom::GLGetnMinmax glGetnMinmax = nullptr;
boom::GLTextureBarrier glTextureBarrier = nullptr;
boom::GLSpecializeShader glSpecializeShader = nullptr;
boom::GLMultiDrawArraysIndirectCount glMultiDrawArraysIndirectCount = nullptr;
boom::GLMultiDrawElementsIndirectCount glMultiDrawElementsIndirectCount = nullptr;
boom::GLPolygonOffsetClamp glPolygonOffsetClamp = nullptr;
boom::GLBlendBarrier glBlendBarrier = nullptr;
boom::GLPrimitiveBoundingBox glPrimitiveBoundingBox = nullptr;
/* #endregion */

OpenGL::~OpenGL() {
    _implDone();
}

OpenGL::OpenGL(boom::OpenGLOptions const& options)
	: _impl(nullptr)
{
    _implInit(options);
    _current();
    _bootstrap();
}

void OpenGL::cullFace(std::uint32_t mode) {
    _current();
    boom::glCullFace(mode);
}

void OpenGL::frontFace(std::uint32_t mode) {
    _current();
    boom::glFrontFace(mode);
}

void OpenGL::hint(std::uint32_t target, std::uint32_t mode) {
    _current();
    boom::glHint(target, mode);
}

void OpenGL::lineWidth(float width) {
    _current();
    boom::glLineWidth(width);
}

void OpenGL::pointSize(float size) {
    _current();
    boom::glPointSize(size);
}

void OpenGL::polygonMode(std::uint32_t face, std::uint32_t mode) {
    _current();
    boom::glPolygonMode(face, mode);
}

void OpenGL::scissor(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
    _current();
    boom::glScissor(x, y, width, height);
}

void OpenGL::texParameterf(std::uint32_t target, std::uint32_t pname, float param) {
    _current();
    boom::glTexParameterf(target, pname, param);
}

void OpenGL::texParameterfv(std::uint32_t target, std::uint32_t pname, float const* params) {
    _current();
    boom::glTexParameterfv(target, pname, params);
}

void OpenGL::texParameteri(std::uint32_t target, std::uint32_t pname, std::int32_t param) {
    _current();
    boom::glTexParameteri(target, pname, param);
}

void OpenGL::texParameteriv(std::uint32_t target, std::uint32_t pname, std::int32_t const* params) {
    _current();
    boom::glTexParameteriv(target, pname, params);
}

void OpenGL::texImage1D(std::uint32_t target, std::int32_t level, std::int32_t internalformat, std::int32_t width, std::int32_t border, std::uint32_t format, std::uint32_t type, void const* pixels) {
    _current();
    boom::glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
}

void OpenGL::texImage2D(std::uint32_t target, std::int32_t level, std::int32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t border, std::uint32_t format, std::uint32_t type, void const* pixels) {
    _current();
    boom::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void OpenGL::drawBuffer(std::uint32_t buf) {
    _current();
    boom::glDrawBuffer(buf);
}

void OpenGL::clear(std::uint32_t mask) {
    _current();
    boom::glClear(mask);
}

void OpenGL::clearColor(float red, float green, float blue, float alpha) {
    _current();
    boom::glClearColor(red, green, blue, alpha);
}

void OpenGL::clearStencil(std::int32_t s) {
    _current();
    boom::glClearStencil(s);
}

void OpenGL::clearDepth(double depth) {
    _current();
    boom::glClearDepth(depth);
}

void OpenGL::stencilMask(std::uint32_t mask) {
    _current();
    boom::glStencilMask(mask);
}

void OpenGL::colorMask(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) {
    _current();
    boom::glColorMask(red, green, blue, alpha);
}

void OpenGL::depthMask(std::uint8_t flag) {
    _current();
    boom::glDepthMask(flag);
}

void OpenGL::disable(std::uint32_t cap) {
    _current();
    boom::glDisable(cap);
}

void OpenGL::enable(std::uint32_t cap) {
    _current();
    boom::glEnable(cap);
}

void OpenGL::finish() {
    _current();
    boom::glFinish();
}

void OpenGL::flush() {
    _current();
    boom::glFlush();
}

void OpenGL::blendFunc(std::uint32_t sfactor, std::uint32_t dfactor) {
    _current();
    boom::glBlendFunc(sfactor, dfactor);
}

void OpenGL::logicOp(std::uint32_t opcode) {
    _current();
    boom::glLogicOp(opcode);
}

void OpenGL::stencilFunc(std::uint32_t func, std::int32_t ref, std::uint32_t mask) {
    _current();
    boom::glStencilFunc(func, ref, mask);
}

void OpenGL::stencilOp(std::uint32_t fail, std::uint32_t zfail, std::uint32_t zpass) {
    _current();
    boom::glStencilOp(fail, zfail, zpass);
}

void OpenGL::depthFunc(std::uint32_t func) {
    _current();
    boom::glDepthFunc(func);
}

void OpenGL::pixelStoref(std::uint32_t pname, float param) {
    _current();
    boom::glPixelStoref(pname, param);
}

void OpenGL::pixelStorei(std::uint32_t pname, std::int32_t param) {
    _current();
    boom::glPixelStorei(pname, param);
}

void OpenGL::readBuffer(std::uint32_t src) {
    _current();
    boom::glReadBuffer(src);
}

void OpenGL::readPixels(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint32_t format, std::uint32_t type, void* pixels) {
    _current();
    boom::glReadPixels(x, y, width, height, format, type, pixels);
}

void OpenGL::getBooleanv(std::uint32_t pname, std::uint8_t* data) {
    _current();
    boom::glGetBooleanv(pname, data);
}

void OpenGL::getDoublev(std::uint32_t pname, double* data) {
    _current();
    boom::glGetDoublev(pname, data);
}

void OpenGL::getFloatv(std::uint32_t pname, float* data) {
    _current();
    boom::glGetFloatv(pname, data);
}

void OpenGL::getIntegerv(std::uint32_t pname, std::int32_t* data) {
    _current();
    boom::glGetIntegerv(pname, data);
}

void OpenGL::getTexImage(std::uint32_t target, std::int32_t level, std::uint32_t format, std::uint32_t type, void* pixels) {
    _current();
    boom::glGetTexImage(target, level, format, type, pixels);
}

void OpenGL::getTexParameterfv(std::uint32_t target, std::uint32_t pname, float* params) {
    _current();
    boom::glGetTexParameterfv(target, pname, params);
}

void OpenGL::getTexParameteriv(std::uint32_t target, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetTexParameteriv(target, pname, params);
}

void OpenGL::getTexLevelParameterfv(std::uint32_t target, std::int32_t level, std::uint32_t pname, float* params) {
    _current();
    boom::glGetTexLevelParameterfv(target, level, pname, params);
}

void OpenGL::getTexLevelParameteriv(std::uint32_t target, std::int32_t level, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetTexLevelParameteriv(target, level, pname, params);
}

void OpenGL::depthRange(double n, double f) {
    _current();
    boom::glDepthRange(n, f);
}

void OpenGL::viewport(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
    _current();
    boom::glViewport(x, y, width, height);
}

void OpenGL::drawArrays(std::uint32_t mode, std::int32_t first, std::int32_t count) {
    _current();
    boom::glDrawArrays(mode, first, count);
}

void OpenGL::drawElements(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const* indices) {
    _current();
    boom::glDrawElements(mode, count, type, indices);
}

void OpenGL::polygonOffset(float factor, float units) {
    _current();
    boom::glPolygonOffset(factor, units);
}

void OpenGL::copyTexImage1D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t border) {
    _current();
    boom::glCopyTexImage1D(target, level, internalformat, x, y, width, border);
}

void OpenGL::copyTexImage2D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::int32_t border) {
    _current();
    boom::glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void OpenGL::copyTexSubImage1D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t x, std::int32_t y, std::int32_t width) {
    _current();
    boom::glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

void OpenGL::copyTexSubImage2D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
    _current();
    boom::glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

void OpenGL::texSubImage1D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t width, std::uint32_t format, std::uint32_t type, void const* pixels) {
    _current();
    boom::glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

void OpenGL::texSubImage2D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t width, std::int32_t height, std::uint32_t format, std::uint32_t type, void const* pixels) {
    _current();
    boom::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void OpenGL::bindTexture(std::uint32_t target, std::uint32_t texture) {
    _current();
    boom::glBindTexture(target, texture);
}

void OpenGL::deleteTextures(std::int32_t n, std::uint32_t const* textures) {
    _current();
    boom::glDeleteTextures(n, textures);
}

void OpenGL::genTextures(std::int32_t n, std::uint32_t* textures) {
    _current();
    boom::glGenTextures(n, textures);
}

void OpenGL::drawRangeElements(std::uint32_t mode, std::uint32_t start, std::uint32_t end, std::int32_t count, std::uint32_t type, void const* indices) {
    _current();
    boom::glDrawRangeElements(mode, start, end, count, type, indices);
}

void OpenGL::texImage3D(std::uint32_t target, std::int32_t level, std::int32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth, std::int32_t border, std::uint32_t format, std::uint32_t type, void const* pixels) {
    _current();
    boom::glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

void OpenGL::texSubImage3D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint32_t format, std::uint32_t type, void const* pixels) {
    _current();
    boom::glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void OpenGL::copyTexSubImage3D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
    _current();
    boom::glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void OpenGL::activeTexture(std::uint32_t texture) {
    _current();
    boom::glActiveTexture(texture);
}

void OpenGL::sampleCoverage(float value, std::uint8_t invert) {
    _current();
    boom::glSampleCoverage(value, invert);
}

void OpenGL::compressedTexImage3D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth, std::int32_t border, std::int32_t imageSize, void const* data) {
    _current();
    boom::glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}

void OpenGL::compressedTexImage2D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t border, std::int32_t imageSize, void const* data) {
    _current();
    boom::glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

void OpenGL::compressedTexImage1D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t width, std::int32_t border, std::int32_t imageSize, void const* data) {
    _current();
    boom::glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
}

void OpenGL::compressedTexSubImage3D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint32_t format, std::int32_t imageSize, void const* data) {
    _current();
    boom::glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void OpenGL::compressedTexSubImage2D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t width, std::int32_t height, std::uint32_t format, std::int32_t imageSize, void const* data) {
    _current();
    boom::glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void OpenGL::compressedTexSubImage1D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t width, std::uint32_t format, std::int32_t imageSize, void const* data) {
    _current();
    boom::glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
}

void OpenGL::getCompressedTexImage(std::uint32_t target, std::int32_t level, void* img) {
    _current();
    boom::glGetCompressedTexImage(target, level, img);
}

void OpenGL::blendFuncSeparate(std::uint32_t sfactorRGB, std::uint32_t dfactorRGB, std::uint32_t sfactorAlpha, std::uint32_t dfactorAlpha) {
    _current();
    boom::glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void OpenGL::multiDrawArrays(std::uint32_t mode, std::int32_t const* first, std::int32_t const* count, std::int32_t drawcount) {
    _current();
    boom::glMultiDrawArrays(mode, first, count, drawcount);
}

void OpenGL::multiDrawElements(std::uint32_t mode, std::int32_t const* count, std::uint32_t type, void const* const* indices, std::int32_t drawcount) {
    _current();
    boom::glMultiDrawElements(mode, count, type, indices, drawcount);
}

void OpenGL::pointParameterf(std::uint32_t pname, float param) {
    _current();
    boom::glPointParameterf(pname, param);
}

void OpenGL::pointParameterfv(std::uint32_t pname, float const* params) {
    _current();
    boom::glPointParameterfv(pname, params);
}

void OpenGL::pointParameteri(std::uint32_t pname, std::int32_t param) {
    _current();
    boom::glPointParameteri(pname, param);
}

void OpenGL::pointParameteriv(std::uint32_t pname, std::int32_t const* params) {
    _current();
    boom::glPointParameteriv(pname, params);
}

void OpenGL::blendColor(float red, float green, float blue, float alpha) {
    _current();
    boom::glBlendColor(red, green, blue, alpha);
}

void OpenGL::blendEquation(std::uint32_t mode) {
    _current();
    boom::glBlendEquation(mode);
}

void OpenGL::genQueries(std::int32_t n, std::uint32_t* ids) {
    _current();
    boom::glGenQueries(n, ids);
}

void OpenGL::deleteQueries(std::int32_t n, std::uint32_t const* ids) {
    _current();
    boom::glDeleteQueries(n, ids);
}

void OpenGL::beginQuery(std::uint32_t target, std::uint32_t id) {
    _current();
    boom::glBeginQuery(target, id);
}

void OpenGL::endQuery(std::uint32_t target) {
    _current();
    boom::glEndQuery(target);
}

void OpenGL::getQueryiv(std::uint32_t target, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetQueryiv(target, pname, params);
}

void OpenGL::getQueryObjectiv(std::uint32_t id, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetQueryObjectiv(id, pname, params);
}

void OpenGL::getQueryObjectuiv(std::uint32_t id, std::uint32_t pname, std::uint32_t* params) {
    _current();
    boom::glGetQueryObjectuiv(id, pname, params);
}

void OpenGL::bindBuffer(std::uint32_t target, std::uint32_t buffer) {
    _current();
    boom::glBindBuffer(target, buffer);
}

void OpenGL::deleteBuffers(std::int32_t n, std::uint32_t const* buffers) {
    _current();
    boom::glDeleteBuffers(n, buffers);
}

void OpenGL::genBuffers(std::int32_t n, std::uint32_t* buffers) {
    _current();
    boom::glGenBuffers(n, buffers);
}

void OpenGL::bufferData(std::uint32_t target, std::int64_t size, void const* data, std::uint32_t usage) {
    _current();
    boom::glBufferData(target, size, data, usage);
}

void OpenGL::bufferSubData(std::uint32_t target, std::intptr_t offset, std::int64_t size, void const* data) {
    _current();
    boom::glBufferSubData(target, offset, size, data);
}

void OpenGL::getBufferSubData(std::uint32_t target, std::intptr_t offset, std::int64_t size, void* data) {
    _current();
    boom::glGetBufferSubData(target, offset, size, data);
}

void OpenGL::getBufferParameteriv(std::uint32_t target, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetBufferParameteriv(target, pname, params);
}

void OpenGL::getBufferPointerv(std::uint32_t target, std::uint32_t pname, void** params) {
    _current();
    boom::glGetBufferPointerv(target, pname, params);
}

void OpenGL::blendEquationSeparate(std::uint32_t modeRGB, std::uint32_t modeAlpha) {
    _current();
    boom::glBlendEquationSeparate(modeRGB, modeAlpha);
}

void OpenGL::drawBuffers(std::int32_t n, std::uint32_t const* bufs) {
    _current();
    boom::glDrawBuffers(n, bufs);
}

void OpenGL::stencilOpSeparate(std::uint32_t face, std::uint32_t sfail, std::uint32_t dpfail, std::uint32_t dppass) {
    _current();
    boom::glStencilOpSeparate(face, sfail, dpfail, dppass);
}

void OpenGL::stencilFuncSeparate(std::uint32_t face, std::uint32_t func, std::int32_t ref, std::uint32_t mask) {
    _current();
    boom::glStencilFuncSeparate(face, func, ref, mask);
}

void OpenGL::stencilMaskSeparate(std::uint32_t face, std::uint32_t mask) {
    _current();
    boom::glStencilMaskSeparate(face, mask);
}

void OpenGL::attachShader(std::uint32_t program, std::uint32_t shader) {
    _current();
    boom::glAttachShader(program, shader);
}

void OpenGL::bindAttribLocation(std::uint32_t program, std::uint32_t index, char const* name) {
    _current();
    boom::glBindAttribLocation(program, index, name);
}

void OpenGL::compileShader(std::uint32_t shader) {
    _current();
    boom::glCompileShader(shader);
}

void OpenGL::deleteProgram(std::uint32_t program) {
    _current();
    boom::glDeleteProgram(program);
}

void OpenGL::deleteShader(std::uint32_t shader) {
    _current();
    boom::glDeleteShader(shader);
}

void OpenGL::detachShader(std::uint32_t program, std::uint32_t shader) {
    _current();
    boom::glDetachShader(program, shader);
}

void OpenGL::disableVertexAttribArray(std::uint32_t index) {
    _current();
    boom::glDisableVertexAttribArray(index);
}

void OpenGL::enableVertexAttribArray(std::uint32_t index) {
    _current();
    boom::glEnableVertexAttribArray(index);
}

void OpenGL::getActiveAttrib(std::uint32_t program, std::uint32_t index, std::int32_t bufSize, std::int32_t* length, std::int32_t* size, std::uint32_t* type, char* name) {
    _current();
    boom::glGetActiveAttrib(program, index, bufSize, length, size, type, name);
}

void OpenGL::getActiveUniform(std::uint32_t program, std::uint32_t index, std::int32_t bufSize, std::int32_t* length, std::int32_t* size, std::uint32_t* type, char* name) {
    _current();
    boom::glGetActiveUniform(program, index, bufSize, length, size, type, name);
}

void OpenGL::getAttachedShaders(std::uint32_t program, std::int32_t maxCount, std::int32_t* count, std::uint32_t* shaders) {
    _current();
    boom::glGetAttachedShaders(program, maxCount, count, shaders);
}

void OpenGL::getProgramiv(std::uint32_t program, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetProgramiv(program, pname, params);
}

void OpenGL::getProgramInfoLog(std::uint32_t program, std::int32_t bufSize, std::int32_t* length, char* infoLog) {
    _current();
    boom::glGetProgramInfoLog(program, bufSize, length, infoLog);
}

void OpenGL::getShaderiv(std::uint32_t shader, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetShaderiv(shader, pname, params);
}

void OpenGL::getShaderInfoLog(std::uint32_t shader, std::int32_t bufSize, std::int32_t* length, char* infoLog) {
    _current();
    boom::glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

void OpenGL::getShaderSource(std::uint32_t shader, std::int32_t bufSize, std::int32_t* length, char* source) {
    _current();
    boom::glGetShaderSource(shader, bufSize, length, source);
}

void OpenGL::getUniformfv(std::uint32_t program, std::int32_t location, float* params) {
    _current();
    boom::glGetUniformfv(program, location, params);
}

void OpenGL::getUniformiv(std::uint32_t program, std::int32_t location, std::int32_t* params) {
    _current();
    boom::glGetUniformiv(program, location, params);
}

void OpenGL::getVertexAttribdv(std::uint32_t index, std::uint32_t pname, double* params) {
    _current();
    boom::glGetVertexAttribdv(index, pname, params);
}

void OpenGL::getVertexAttribfv(std::uint32_t index, std::uint32_t pname, float* params) {
    _current();
    boom::glGetVertexAttribfv(index, pname, params);
}

void OpenGL::getVertexAttribiv(std::uint32_t index, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetVertexAttribiv(index, pname, params);
}

void OpenGL::getVertexAttribPointerv(std::uint32_t index, std::uint32_t pname, void** pointer) {
    _current();
    boom::glGetVertexAttribPointerv(index, pname, pointer);
}

void OpenGL::linkProgram(std::uint32_t program) {
    _current();
    boom::glLinkProgram(program);
}

void OpenGL::shaderSource(std::uint32_t shader, std::int32_t count, char const** string, std::int32_t const* length) {
    _current();
    boom::glShaderSource(shader, count, string, length);
}

void OpenGL::useProgram(std::uint32_t program) {
    _current();
    boom::glUseProgram(program);
}

void OpenGL::uniform1f(std::int32_t location, float v0) {
    _current();
    boom::glUniform1f(location, v0);
}

void OpenGL::uniform2f(std::int32_t location, float v0, float v1) {
    _current();
    boom::glUniform2f(location, v0, v1);
}

void OpenGL::uniform3f(std::int32_t location, float v0, float v1, float v2) {
    _current();
    boom::glUniform3f(location, v0, v1, v2);
}

void OpenGL::uniform4f(std::int32_t location, float v0, float v1, float v2, float v3) {
    _current();
    boom::glUniform4f(location, v0, v1, v2, v3);
}

void OpenGL::uniform1i(std::int32_t location, std::int32_t v0) {
    _current();
    boom::glUniform1i(location, v0);
}

void OpenGL::uniform2i(std::int32_t location, std::int32_t v0, std::int32_t v1) {
    _current();
    boom::glUniform2i(location, v0, v1);
}

void OpenGL::uniform3i(std::int32_t location, std::int32_t v0, std::int32_t v1, std::int32_t v2) {
    _current();
    boom::glUniform3i(location, v0, v1, v2);
}

void OpenGL::uniform4i(std::int32_t location, std::int32_t v0, std::int32_t v1, std::int32_t v2, std::int32_t v3) {
    _current();
    boom::glUniform4i(location, v0, v1, v2, v3);
}

void OpenGL::uniform1fv(std::int32_t location, std::int32_t count, float const* value) {
    _current();
    boom::glUniform1fv(location, count, value);
}

void OpenGL::uniform2fv(std::int32_t location, std::int32_t count, float const* value) {
    _current();
    boom::glUniform2fv(location, count, value);
}

void OpenGL::uniform3fv(std::int32_t location, std::int32_t count, float const* value) {
    _current();
    boom::glUniform3fv(location, count, value);
}

void OpenGL::uniform4fv(std::int32_t location, std::int32_t count, float const* value) {
    _current();
    boom::glUniform4fv(location, count, value);
}

void OpenGL::uniform1iv(std::int32_t location, std::int32_t count, std::int32_t const* value) {
    _current();
    boom::glUniform1iv(location, count, value);
}

void OpenGL::uniform2iv(std::int32_t location, std::int32_t count, std::int32_t const* value) {
    _current();
    boom::glUniform2iv(location, count, value);
}

void OpenGL::uniform3iv(std::int32_t location, std::int32_t count, std::int32_t const* value) {
    _current();
    boom::glUniform3iv(location, count, value);
}

void OpenGL::uniform4iv(std::int32_t location, std::int32_t count, std::int32_t const* value) {
    _current();
    boom::glUniform4iv(location, count, value);
}

void OpenGL::uniformMatrix2fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glUniformMatrix2fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glUniformMatrix3fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glUniformMatrix4fv(location, count, transpose, value);
}

void OpenGL::validateProgram(std::uint32_t program) {
    _current();
    boom::glValidateProgram(program);
}

void OpenGL::vertexAttrib1d(std::uint32_t index, double x) {
    _current();
    boom::glVertexAttrib1d(index, x);
}

void OpenGL::vertexAttrib1dv(std::uint32_t index, double const* v) {
    _current();
    boom::glVertexAttrib1dv(index, v);
}

void OpenGL::vertexAttrib1f(std::uint32_t index, float x) {
    _current();
    boom::glVertexAttrib1f(index, x);
}

void OpenGL::vertexAttrib1fv(std::uint32_t index, float const* v) {
    _current();
    boom::glVertexAttrib1fv(index, v);
}

void OpenGL::vertexAttrib1s(std::uint32_t index, std::int16_t x) {
    _current();
    boom::glVertexAttrib1s(index, x);
}

void OpenGL::vertexAttrib1sv(std::uint32_t index, std::int16_t const* v) {
    _current();
    boom::glVertexAttrib1sv(index, v);
}

void OpenGL::vertexAttrib2d(std::uint32_t index, double x, double y) {
    _current();
    boom::glVertexAttrib2d(index, x, y);
}

void OpenGL::vertexAttrib2dv(std::uint32_t index, double const* v) {
    _current();
    boom::glVertexAttrib2dv(index, v);
}

void OpenGL::vertexAttrib2f(std::uint32_t index, float x, float y) {
    _current();
    boom::glVertexAttrib2f(index, x, y);
}

void OpenGL::vertexAttrib2fv(std::uint32_t index, float const* v) {
    _current();
    boom::glVertexAttrib2fv(index, v);
}

void OpenGL::vertexAttrib2s(std::uint32_t index, std::int16_t x, std::int16_t y) {
    _current();
    boom::glVertexAttrib2s(index, x, y);
}

void OpenGL::vertexAttrib2sv(std::uint32_t index, std::int16_t const* v) {
    _current();
    boom::glVertexAttrib2sv(index, v);
}

void OpenGL::vertexAttrib3d(std::uint32_t index, double x, double y, double z) {
    _current();
    boom::glVertexAttrib3d(index, x, y, z);
}

void OpenGL::vertexAttrib3dv(std::uint32_t index, double const* v) {
    _current();
    boom::glVertexAttrib3dv(index, v);
}

void OpenGL::vertexAttrib3f(std::uint32_t index, float x, float y, float z) {
    _current();
    boom::glVertexAttrib3f(index, x, y, z);
}

void OpenGL::vertexAttrib3fv(std::uint32_t index, float const* v) {
    _current();
    boom::glVertexAttrib3fv(index, v);
}

void OpenGL::vertexAttrib3s(std::uint32_t index, std::int16_t x, std::int16_t y, std::int16_t z) {
    _current();
    boom::glVertexAttrib3s(index, x, y, z);
}

void OpenGL::vertexAttrib3sv(std::uint32_t index, std::int16_t const* v) {
    _current();
    boom::glVertexAttrib3sv(index, v);
}

void OpenGL::vertexAttrib4Nbv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glVertexAttrib4Nbv(index, v);
}

void OpenGL::vertexAttrib4Niv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glVertexAttrib4Niv(index, v);
}

void OpenGL::vertexAttrib4Nsv(std::uint32_t index, std::int16_t const* v) {
    _current();
    boom::glVertexAttrib4Nsv(index, v);
}

void OpenGL::vertexAttrib4Nub(std::uint32_t index, std::uint8_t x, std::uint8_t y, std::uint8_t z, std::uint8_t w) {
    _current();
    boom::glVertexAttrib4Nub(index, x, y, z, w);
}

void OpenGL::vertexAttrib4Nubv(std::uint32_t index, std::uint8_t const* v) {
    _current();
    boom::glVertexAttrib4Nubv(index, v);
}

void OpenGL::vertexAttrib4Nuiv(std::uint32_t index, std::uint32_t const* v) {
    _current();
    boom::glVertexAttrib4Nuiv(index, v);
}

void OpenGL::vertexAttrib4Nusv(std::uint32_t index, std::uint16_t const* v) {
    _current();
    boom::glVertexAttrib4Nusv(index, v);
}

void OpenGL::vertexAttrib4bv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glVertexAttrib4bv(index, v);
}

void OpenGL::vertexAttrib4d(std::uint32_t index, double x, double y, double z, double w) {
    _current();
    boom::glVertexAttrib4d(index, x, y, z, w);
}

void OpenGL::vertexAttrib4dv(std::uint32_t index, double const* v) {
    _current();
    boom::glVertexAttrib4dv(index, v);
}

void OpenGL::vertexAttrib4f(std::uint32_t index, float x, float y, float z, float w) {
    _current();
    boom::glVertexAttrib4f(index, x, y, z, w);
}

void OpenGL::vertexAttrib4fv(std::uint32_t index, float const* v) {
    _current();
    boom::glVertexAttrib4fv(index, v);
}

void OpenGL::vertexAttrib4iv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glVertexAttrib4iv(index, v);
}

void OpenGL::vertexAttrib4s(std::uint32_t index, std::int16_t x, std::int16_t y, std::int16_t z, std::int16_t w) {
    _current();
    boom::glVertexAttrib4s(index, x, y, z, w);
}

void OpenGL::vertexAttrib4sv(std::uint32_t index, std::int16_t const* v) {
    _current();
    boom::glVertexAttrib4sv(index, v);
}

void OpenGL::vertexAttrib4ubv(std::uint32_t index, std::uint8_t const* v) {
    _current();
    boom::glVertexAttrib4ubv(index, v);
}

void OpenGL::vertexAttrib4uiv(std::uint32_t index, std::uint32_t const* v) {
    _current();
    boom::glVertexAttrib4uiv(index, v);
}

void OpenGL::vertexAttrib4usv(std::uint32_t index, std::uint16_t const* v) {
    _current();
    boom::glVertexAttrib4usv(index, v);
}

void OpenGL::vertexAttribPointer(std::uint32_t index, std::int32_t size, std::uint32_t type, std::uint8_t normalized, std::int32_t stride, void const* pointer) {
    _current();
    boom::glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void OpenGL::uniformMatrix2x3fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glUniformMatrix2x3fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3x2fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glUniformMatrix3x2fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix2x4fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glUniformMatrix2x4fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4x2fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glUniformMatrix4x2fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3x4fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glUniformMatrix3x4fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4x3fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glUniformMatrix4x3fv(location, count, transpose, value);
}

void OpenGL::colorMaski(std::uint32_t index, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
    _current();
    boom::glColorMaski(index, r, g, b, a);
}

void OpenGL::getBooleani_v(std::uint32_t target, std::uint32_t index, std::uint8_t* data) {
    _current();
    boom::glGetBooleani_v(target, index, data);
}

void OpenGL::getIntegeri_v(std::uint32_t target, std::uint32_t index, std::int32_t* data) {
    _current();
    boom::glGetIntegeri_v(target, index, data);
}

void OpenGL::enablei(std::uint32_t target, std::uint32_t index) {
    _current();
    boom::glEnablei(target, index);
}

void OpenGL::disablei(std::uint32_t target, std::uint32_t index) {
    _current();
    boom::glDisablei(target, index);
}

void OpenGL::beginTransformFeedback(std::uint32_t primitiveMode) {
    _current();
    boom::glBeginTransformFeedback(primitiveMode);
}

void OpenGL::endTransformFeedback() {
    _current();
    boom::glEndTransformFeedback();
}

void OpenGL::bindBufferRange(std::uint32_t target, std::uint32_t index, std::uint32_t buffer, std::intptr_t offset, std::int64_t size) {
    _current();
    boom::glBindBufferRange(target, index, buffer, offset, size);
}

void OpenGL::bindBufferBase(std::uint32_t target, std::uint32_t index, std::uint32_t buffer) {
    _current();
    boom::glBindBufferBase(target, index, buffer);
}

void OpenGL::transformFeedbackVaryings(std::uint32_t program, std::int32_t count, char const* const* varyings, std::uint32_t bufferMode) {
    _current();
    boom::glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}

void OpenGL::getTransformFeedbackVarying(std::uint32_t program, std::uint32_t index, std::int32_t bufSize, std::int32_t* length, std::int32_t* size, std::uint32_t* type, char* name) {
    _current();
    boom::glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}

void OpenGL::clampColor(std::uint32_t target, std::uint32_t clamp) {
    _current();
    boom::glClampColor(target, clamp);
}

void OpenGL::beginConditionalRender(std::uint32_t id, std::uint32_t mode) {
    _current();
    boom::glBeginConditionalRender(id, mode);
}

void OpenGL::endConditionalRender() {
    _current();
    boom::glEndConditionalRender();
}

void OpenGL::vertexAttribIPointer(std::uint32_t index, std::int32_t size, std::uint32_t type, std::int32_t stride, void const* pointer) {
    _current();
    boom::glVertexAttribIPointer(index, size, type, stride, pointer);
}

void OpenGL::getVertexAttribIiv(std::uint32_t index, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetVertexAttribIiv(index, pname, params);
}

void OpenGL::getVertexAttribIuiv(std::uint32_t index, std::uint32_t pname, std::uint32_t* params) {
    _current();
    boom::glGetVertexAttribIuiv(index, pname, params);
}

void OpenGL::vertexAttribI1i(std::uint32_t index, std::int32_t x) {
    _current();
    boom::glVertexAttribI1i(index, x);
}

void OpenGL::vertexAttribI2i(std::uint32_t index, std::int32_t x, std::int32_t y) {
    _current();
    boom::glVertexAttribI2i(index, x, y);
}

void OpenGL::vertexAttribI3i(std::uint32_t index, std::int32_t x, std::int32_t y, std::int32_t z) {
    _current();
    boom::glVertexAttribI3i(index, x, y, z);
}

void OpenGL::vertexAttribI4i(std::uint32_t index, std::int32_t x, std::int32_t y, std::int32_t z, std::int32_t w) {
    _current();
    boom::glVertexAttribI4i(index, x, y, z, w);
}

void OpenGL::vertexAttribI1ui(std::uint32_t index, std::uint32_t x) {
    _current();
    boom::glVertexAttribI1ui(index, x);
}

void OpenGL::vertexAttribI2ui(std::uint32_t index, std::uint32_t x, std::uint32_t y) {
    _current();
    boom::glVertexAttribI2ui(index, x, y);
}

void OpenGL::vertexAttribI3ui(std::uint32_t index, std::uint32_t x, std::uint32_t y, std::uint32_t z) {
    _current();
    boom::glVertexAttribI3ui(index, x, y, z);
}

void OpenGL::vertexAttribI4ui(std::uint32_t index, std::uint32_t x, std::uint32_t y, std::uint32_t z, std::uint32_t w) {
    _current();
    boom::glVertexAttribI4ui(index, x, y, z, w);
}

void OpenGL::vertexAttribI1iv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glVertexAttribI1iv(index, v);
}

void OpenGL::vertexAttribI2iv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glVertexAttribI2iv(index, v);
}

void OpenGL::vertexAttribI3iv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glVertexAttribI3iv(index, v);
}

void OpenGL::vertexAttribI4iv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glVertexAttribI4iv(index, v);
}

void OpenGL::vertexAttribI1uiv(std::uint32_t index, std::uint32_t const* v) {
    _current();
    boom::glVertexAttribI1uiv(index, v);
}

void OpenGL::vertexAttribI2uiv(std::uint32_t index, std::uint32_t const* v) {
    _current();
    boom::glVertexAttribI2uiv(index, v);
}

void OpenGL::vertexAttribI3uiv(std::uint32_t index, std::uint32_t const* v) {
    _current();
    boom::glVertexAttribI3uiv(index, v);
}

void OpenGL::vertexAttribI4uiv(std::uint32_t index, std::uint32_t const* v) {
    _current();
    boom::glVertexAttribI4uiv(index, v);
}

void OpenGL::vertexAttribI4bv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glVertexAttribI4bv(index, v);
}

void OpenGL::vertexAttribI4sv(std::uint32_t index, std::int16_t const* v) {
    _current();
    boom::glVertexAttribI4sv(index, v);
}

void OpenGL::vertexAttribI4ubv(std::uint32_t index, std::uint8_t const* v) {
    _current();
    boom::glVertexAttribI4ubv(index, v);
}

void OpenGL::vertexAttribI4usv(std::uint32_t index, std::uint16_t const* v) {
    _current();
    boom::glVertexAttribI4usv(index, v);
}

void OpenGL::getUniformuiv(std::uint32_t program, std::int32_t location, std::uint32_t* params) {
    _current();
    boom::glGetUniformuiv(program, location, params);
}

void OpenGL::bindFragDataLocation(std::uint32_t program, std::uint32_t color, char const* name) {
    _current();
    boom::glBindFragDataLocation(program, color, name);
}

void OpenGL::uniform1ui(std::int32_t location, std::uint32_t v0) {
    _current();
    boom::glUniform1ui(location, v0);
}

void OpenGL::uniform2ui(std::int32_t location, std::uint32_t v0, std::uint32_t v1) {
    _current();
    boom::glUniform2ui(location, v0, v1);
}

void OpenGL::uniform3ui(std::int32_t location, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2) {
    _current();
    boom::glUniform3ui(location, v0, v1, v2);
}

void OpenGL::uniform4ui(std::int32_t location, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3) {
    _current();
    boom::glUniform4ui(location, v0, v1, v2, v3);
}

void OpenGL::uniform1uiv(std::int32_t location, std::int32_t count, std::uint32_t const* value) {
    _current();
    boom::glUniform1uiv(location, count, value);
}

void OpenGL::uniform2uiv(std::int32_t location, std::int32_t count, std::uint32_t const* value) {
    _current();
    boom::glUniform2uiv(location, count, value);
}

void OpenGL::uniform3uiv(std::int32_t location, std::int32_t count, std::uint32_t const* value) {
    _current();
    boom::glUniform3uiv(location, count, value);
}

void OpenGL::uniform4uiv(std::int32_t location, std::int32_t count, std::uint32_t const* value) {
    _current();
    boom::glUniform4uiv(location, count, value);
}

void OpenGL::texParameterIiv(std::uint32_t target, std::uint32_t pname, std::int32_t const* params) {
    _current();
    boom::glTexParameterIiv(target, pname, params);
}

void OpenGL::texParameterIuiv(std::uint32_t target, std::uint32_t pname, std::uint32_t const* params) {
    _current();
    boom::glTexParameterIuiv(target, pname, params);
}

void OpenGL::getTexParameterIiv(std::uint32_t target, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetTexParameterIiv(target, pname, params);
}

void OpenGL::getTexParameterIuiv(std::uint32_t target, std::uint32_t pname, std::uint32_t* params) {
    _current();
    boom::glGetTexParameterIuiv(target, pname, params);
}

void OpenGL::clearBufferiv(std::uint32_t buffer, std::int32_t drawbuffer, std::int32_t const* value) {
    _current();
    boom::glClearBufferiv(buffer, drawbuffer, value);
}

void OpenGL::clearBufferuiv(std::uint32_t buffer, std::int32_t drawbuffer, std::uint32_t const* value) {
    _current();
    boom::glClearBufferuiv(buffer, drawbuffer, value);
}

void OpenGL::clearBufferfv(std::uint32_t buffer, std::int32_t drawbuffer, float const* value) {
    _current();
    boom::glClearBufferfv(buffer, drawbuffer, value);
}

void OpenGL::clearBufferfi(std::uint32_t buffer, std::int32_t drawbuffer, float depth, std::int32_t stencil) {
    _current();
    boom::glClearBufferfi(buffer, drawbuffer, depth, stencil);
}

void OpenGL::bindRenderbuffer(std::uint32_t target, std::uint32_t renderbuffer) {
    _current();
    boom::glBindRenderbuffer(target, renderbuffer);
}

void OpenGL::deleteRenderbuffers(std::int32_t n, std::uint32_t const* renderbuffers) {
    _current();
    boom::glDeleteRenderbuffers(n, renderbuffers);
}

void OpenGL::genRenderbuffers(std::int32_t n, std::uint32_t* renderbuffers) {
    _current();
    boom::glGenRenderbuffers(n, renderbuffers);
}

void OpenGL::renderbufferStorage(std::uint32_t target, std::uint32_t internalformat, std::int32_t width, std::int32_t height) {
    _current();
    boom::glRenderbufferStorage(target, internalformat, width, height);
}

void OpenGL::getRenderbufferParameteriv(std::uint32_t target, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetRenderbufferParameteriv(target, pname, params);
}

void OpenGL::bindFramebuffer(std::uint32_t target, std::uint32_t framebuffer) {
    _current();
    boom::glBindFramebuffer(target, framebuffer);
}

void OpenGL::deleteFramebuffers(std::int32_t n, std::uint32_t const* framebuffers) {
    _current();
    boom::glDeleteFramebuffers(n, framebuffers);
}

void OpenGL::genFramebuffers(std::int32_t n, std::uint32_t* framebuffers) {
    _current();
    boom::glGenFramebuffers(n, framebuffers);
}

void OpenGL::framebufferTexture1D(std::uint32_t target, std::uint32_t attachment, std::uint32_t textarget, std::uint32_t texture, std::int32_t level) {
    _current();
    boom::glFramebufferTexture1D(target, attachment, textarget, texture, level);
}

void OpenGL::framebufferTexture2D(std::uint32_t target, std::uint32_t attachment, std::uint32_t textarget, std::uint32_t texture, std::int32_t level) {
    _current();
    boom::glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void OpenGL::framebufferTexture3D(std::uint32_t target, std::uint32_t attachment, std::uint32_t textarget, std::uint32_t texture, std::int32_t level, std::int32_t zoffset) {
    _current();
    boom::glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
}

void OpenGL::framebufferRenderbuffer(std::uint32_t target, std::uint32_t attachment, std::uint32_t renderbuffertarget, std::uint32_t renderbuffer) {
    _current();
    boom::glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void OpenGL::getFramebufferAttachmentParameteriv(std::uint32_t target, std::uint32_t attachment, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

void OpenGL::generateMipmap(std::uint32_t target) {
    _current();
    boom::glGenerateMipmap(target);
}

void OpenGL::blitFramebuffer(std::int32_t srcX0, std::int32_t srcY0, std::int32_t srcX1, std::int32_t srcY1, std::int32_t dstX0, std::int32_t dstY0, std::int32_t dstX1, std::int32_t dstY1, std::uint32_t mask, std::uint32_t filter) {
    _current();
    boom::glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void OpenGL::renderbufferStorageMultisample(std::uint32_t target, std::int32_t samples, std::uint32_t internalformat, std::int32_t width, std::int32_t height) {
    _current();
    boom::glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

void OpenGL::framebufferTextureLayer(std::uint32_t target, std::uint32_t attachment, std::uint32_t texture, std::int32_t level, std::int32_t layer) {
    _current();
    boom::glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

void OpenGL::flushMappedBufferRange(std::uint32_t target, std::intptr_t offset, std::int64_t length) {
    _current();
    boom::glFlushMappedBufferRange(target, offset, length);
}

void OpenGL::bindVertexArray(std::uint32_t array) {
    _current();
    boom::glBindVertexArray(array);
}

void OpenGL::deleteVertexArrays(std::int32_t n, std::uint32_t const* arrays) {
    _current();
    boom::glDeleteVertexArrays(n, arrays);
}

void OpenGL::genVertexArrays(std::int32_t n, std::uint32_t* arrays) {
    _current();
    boom::glGenVertexArrays(n, arrays);
}

void OpenGL::drawArraysInstanced(std::uint32_t mode, std::int32_t first, std::int32_t count, std::int32_t instancecount) {
    _current();
    boom::glDrawArraysInstanced(mode, first, count, instancecount);
}

void OpenGL::drawElementsInstanced(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const* indices, std::int32_t instancecount) {
    _current();
    boom::glDrawElementsInstanced(mode, count, type, indices, instancecount);
}

void OpenGL::texBuffer(std::uint32_t target, std::uint32_t internalformat, std::uint32_t buffer) {
    _current();
    boom::glTexBuffer(target, internalformat, buffer);
}

void OpenGL::primitiveRestartIndex(std::uint32_t index) {
    _current();
    boom::glPrimitiveRestartIndex(index);
}

void OpenGL::copyBufferSubData(std::uint32_t readTarget, std::uint32_t writeTarget, std::intptr_t readOffset, std::intptr_t writeOffset, std::int64_t size) {
    _current();
    boom::glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}

void OpenGL::getUniformIndices(std::uint32_t program, std::int32_t uniformCount, char const* const* uniformNames, std::uint32_t* uniformIndices) {
    _current();
    boom::glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
}

void OpenGL::getActiveUniformsiv(std::uint32_t program, std::int32_t uniformCount, std::uint32_t const* uniformIndices, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
}

void OpenGL::getActiveUniformName(std::uint32_t program, std::uint32_t uniformIndex, std::int32_t bufSize, std::int32_t* length, char* uniformName) {
    _current();
    boom::glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
}

void OpenGL::getActiveUniformBlockiv(std::uint32_t program, std::uint32_t uniformBlockIndex, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
}

void OpenGL::getActiveUniformBlockName(std::uint32_t program, std::uint32_t uniformBlockIndex, std::int32_t bufSize, std::int32_t* length, char* uniformBlockName) {
    _current();
    boom::glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}

void OpenGL::uniformBlockBinding(std::uint32_t program, std::uint32_t uniformBlockIndex, std::uint32_t uniformBlockBinding) {
    _current();
    boom::glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}

void OpenGL::drawElementsBaseVertex(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const* indices, std::int32_t basevertex) {
    _current();
    boom::glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
}

void OpenGL::drawRangeElementsBaseVertex(std::uint32_t mode, std::uint32_t start, std::uint32_t end, std::int32_t count, std::uint32_t type, void const* indices, std::int32_t basevertex) {
    _current();
    boom::glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
}

void OpenGL::drawElementsInstancedBaseVertex(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const* indices, std::int32_t instancecount, std::int32_t basevertex) {
    _current();
    boom::glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
}

void OpenGL::multiDrawElementsBaseVertex(std::uint32_t mode, std::int32_t const* count, std::uint32_t type, void const* const* indices, std::int32_t drawcount, std::int32_t const* basevertex) {
    _current();
    boom::glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
}

void OpenGL::provokingVertex(std::uint32_t mode) {
    _current();
    boom::glProvokingVertex(mode);
}

void OpenGL::deleteSync(void* sync) {
    _current();
    boom::glDeleteSync(sync);
}

void OpenGL::waitSync(void* sync, std::uint32_t flags, std::uint64_t timeout) {
    _current();
    boom::glWaitSync(sync, flags, timeout);
}

void OpenGL::getInteger64v(std::uint32_t pname, std::int64_t* data) {
    _current();
    boom::glGetInteger64v(pname, data);
}

void OpenGL::getSynciv(void* sync, std::uint32_t pname, std::int32_t count, std::int32_t* length, std::int32_t* values) {
    _current();
    boom::glGetSynciv(sync, pname, count, length, values);
}

void OpenGL::getInteger64i_v(std::uint32_t target, std::uint32_t index, std::int64_t* data) {
    _current();
    boom::glGetInteger64i_v(target, index, data);
}

void OpenGL::getBufferParameteri64v(std::uint32_t target, std::uint32_t pname, std::int64_t* params) {
    _current();
    boom::glGetBufferParameteri64v(target, pname, params);
}

void OpenGL::framebufferTexture(std::uint32_t target, std::uint32_t attachment, std::uint32_t texture, std::int32_t level) {
    _current();
    boom::glFramebufferTexture(target, attachment, texture, level);
}

void OpenGL::texImage2DMultisample(std::uint32_t target, std::int32_t samples, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::uint8_t fixedsamplelocations) {
    _current();
    boom::glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

void OpenGL::texImage3DMultisample(std::uint32_t target, std::int32_t samples, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint8_t fixedsamplelocations) {
    _current();
    boom::glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

void OpenGL::getMultisamplefv(std::uint32_t pname, std::uint32_t index, float* val) {
    _current();
    boom::glGetMultisamplefv(pname, index, val);
}

void OpenGL::sampleMaski(std::uint32_t maskNumber, std::uint32_t mask) {
    _current();
    boom::glSampleMaski(maskNumber, mask);
}

void OpenGL::bindFragDataLocationIndexed(std::uint32_t program, std::uint32_t colorNumber, std::uint32_t index, char const* name) {
    _current();
    boom::glBindFragDataLocationIndexed(program, colorNumber, index, name);
}

void OpenGL::genSamplers(std::int32_t count, std::uint32_t* samplers) {
    _current();
    boom::glGenSamplers(count, samplers);
}

void OpenGL::deleteSamplers(std::int32_t count, std::uint32_t const* samplers) {
    _current();
    boom::glDeleteSamplers(count, samplers);
}

void OpenGL::bindSampler(std::uint32_t unit, std::uint32_t sampler) {
    _current();
    boom::glBindSampler(unit, sampler);
}

void OpenGL::samplerParameteri(std::uint32_t sampler, std::uint32_t pname, std::int32_t param) {
    _current();
    boom::glSamplerParameteri(sampler, pname, param);
}

void OpenGL::samplerParameteriv(std::uint32_t sampler, std::uint32_t pname, std::int32_t const* param) {
    _current();
    boom::glSamplerParameteriv(sampler, pname, param);
}

void OpenGL::samplerParameterf(std::uint32_t sampler, std::uint32_t pname, float param) {
    _current();
    boom::glSamplerParameterf(sampler, pname, param);
}

void OpenGL::samplerParameterfv(std::uint32_t sampler, std::uint32_t pname, float const* param) {
    _current();
    boom::glSamplerParameterfv(sampler, pname, param);
}

void OpenGL::samplerParameterIiv(std::uint32_t sampler, std::uint32_t pname, std::int32_t const* param) {
    _current();
    boom::glSamplerParameterIiv(sampler, pname, param);
}

void OpenGL::samplerParameterIuiv(std::uint32_t sampler, std::uint32_t pname, std::uint32_t const* param) {
    _current();
    boom::glSamplerParameterIuiv(sampler, pname, param);
}

void OpenGL::getSamplerParameteriv(std::uint32_t sampler, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetSamplerParameteriv(sampler, pname, params);
}

void OpenGL::getSamplerParameterIiv(std::uint32_t sampler, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetSamplerParameterIiv(sampler, pname, params);
}

void OpenGL::getSamplerParameterfv(std::uint32_t sampler, std::uint32_t pname, float* params) {
    _current();
    boom::glGetSamplerParameterfv(sampler, pname, params);
}

void OpenGL::getSamplerParameterIuiv(std::uint32_t sampler, std::uint32_t pname, std::uint32_t* params) {
    _current();
    boom::glGetSamplerParameterIuiv(sampler, pname, params);
}

void OpenGL::queryCounter(std::uint32_t id, std::uint32_t target) {
    _current();
    boom::glQueryCounter(id, target);
}

void OpenGL::getQueryObjecti64v(std::uint32_t id, std::uint32_t pname, std::int64_t* params) {
    _current();
    boom::glGetQueryObjecti64v(id, pname, params);
}

void OpenGL::getQueryObjectui64v(std::uint32_t id, std::uint32_t pname, std::uint64_t* params) {
    _current();
    boom::glGetQueryObjectui64v(id, pname, params);
}

void OpenGL::vertexAttribDivisor(std::uint32_t index, std::uint32_t divisor) {
    _current();
    boom::glVertexAttribDivisor(index, divisor);
}

void OpenGL::vertexAttribP1ui(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t value) {
    _current();
    boom::glVertexAttribP1ui(index, type, normalized, value);
}

void OpenGL::vertexAttribP1uiv(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t const* value) {
    _current();
    boom::glVertexAttribP1uiv(index, type, normalized, value);
}

void OpenGL::vertexAttribP2ui(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t value) {
    _current();
    boom::glVertexAttribP2ui(index, type, normalized, value);
}

void OpenGL::vertexAttribP2uiv(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t const* value) {
    _current();
    boom::glVertexAttribP2uiv(index, type, normalized, value);
}

void OpenGL::vertexAttribP3ui(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t value) {
    _current();
    boom::glVertexAttribP3ui(index, type, normalized, value);
}

void OpenGL::vertexAttribP3uiv(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t const* value) {
    _current();
    boom::glVertexAttribP3uiv(index, type, normalized, value);
}

void OpenGL::vertexAttribP4ui(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t value) {
    _current();
    boom::glVertexAttribP4ui(index, type, normalized, value);
}

void OpenGL::vertexAttribP4uiv(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t const* value) {
    _current();
    boom::glVertexAttribP4uiv(index, type, normalized, value);
}

void OpenGL::vertexP2ui(std::uint32_t type, std::uint32_t value) {
    _current();
    boom::glVertexP2ui(type, value);
}

void OpenGL::vertexP2uiv(std::uint32_t type, std::uint32_t const* value) {
    _current();
    boom::glVertexP2uiv(type, value);
}

void OpenGL::vertexP3ui(std::uint32_t type, std::uint32_t value) {
    _current();
    boom::glVertexP3ui(type, value);
}

void OpenGL::vertexP3uiv(std::uint32_t type, std::uint32_t const* value) {
    _current();
    boom::glVertexP3uiv(type, value);
}

void OpenGL::vertexP4ui(std::uint32_t type, std::uint32_t value) {
    _current();
    boom::glVertexP4ui(type, value);
}

void OpenGL::vertexP4uiv(std::uint32_t type, std::uint32_t const* value) {
    _current();
    boom::glVertexP4uiv(type, value);
}

void OpenGL::texCoordP1ui(std::uint32_t type, std::uint32_t coords) {
    _current();
    boom::glTexCoordP1ui(type, coords);
}

void OpenGL::texCoordP1uiv(std::uint32_t type, std::uint32_t const* coords) {
    _current();
    boom::glTexCoordP1uiv(type, coords);
}

void OpenGL::texCoordP2ui(std::uint32_t type, std::uint32_t coords) {
    _current();
    boom::glTexCoordP2ui(type, coords);
}

void OpenGL::texCoordP2uiv(std::uint32_t type, std::uint32_t const* coords) {
    _current();
    boom::glTexCoordP2uiv(type, coords);
}

void OpenGL::texCoordP3ui(std::uint32_t type, std::uint32_t coords) {
    _current();
    boom::glTexCoordP3ui(type, coords);
}

void OpenGL::texCoordP3uiv(std::uint32_t type, std::uint32_t const* coords) {
    _current();
    boom::glTexCoordP3uiv(type, coords);
}

void OpenGL::texCoordP4ui(std::uint32_t type, std::uint32_t coords) {
    _current();
    boom::glTexCoordP4ui(type, coords);
}

void OpenGL::texCoordP4uiv(std::uint32_t type, std::uint32_t const* coords) {
    _current();
    boom::glTexCoordP4uiv(type, coords);
}

void OpenGL::multiTexCoordP1ui(std::uint32_t texture, std::uint32_t type, std::uint32_t coords) {
    _current();
    boom::glMultiTexCoordP1ui(texture, type, coords);
}

void OpenGL::multiTexCoordP1uiv(std::uint32_t texture, std::uint32_t type, std::uint32_t const* coords) {
    _current();
    boom::glMultiTexCoordP1uiv(texture, type, coords);
}

void OpenGL::multiTexCoordP2ui(std::uint32_t texture, std::uint32_t type, std::uint32_t coords) {
    _current();
    boom::glMultiTexCoordP2ui(texture, type, coords);
}

void OpenGL::multiTexCoordP2uiv(std::uint32_t texture, std::uint32_t type, std::uint32_t const* coords) {
    _current();
    boom::glMultiTexCoordP2uiv(texture, type, coords);
}

void OpenGL::multiTexCoordP3ui(std::uint32_t texture, std::uint32_t type, std::uint32_t coords) {
    _current();
    boom::glMultiTexCoordP3ui(texture, type, coords);
}

void OpenGL::multiTexCoordP3uiv(std::uint32_t texture, std::uint32_t type, std::uint32_t const* coords) {
    _current();
    boom::glMultiTexCoordP3uiv(texture, type, coords);
}

void OpenGL::multiTexCoordP4ui(std::uint32_t texture, std::uint32_t type, std::uint32_t coords) {
    _current();
    boom::glMultiTexCoordP4ui(texture, type, coords);
}

void OpenGL::multiTexCoordP4uiv(std::uint32_t texture, std::uint32_t type, std::uint32_t const* coords) {
    _current();
    boom::glMultiTexCoordP4uiv(texture, type, coords);
}

void OpenGL::normalP3ui(std::uint32_t type, std::uint32_t coords) {
    _current();
    boom::glNormalP3ui(type, coords);
}

void OpenGL::normalP3uiv(std::uint32_t type, std::uint32_t const* coords) {
    _current();
    boom::glNormalP3uiv(type, coords);
}

void OpenGL::colorP3ui(std::uint32_t type, std::uint32_t color) {
    _current();
    boom::glColorP3ui(type, color);
}

void OpenGL::colorP3uiv(std::uint32_t type, std::uint32_t const* color) {
    _current();
    boom::glColorP3uiv(type, color);
}

void OpenGL::colorP4ui(std::uint32_t type, std::uint32_t color) {
    _current();
    boom::glColorP4ui(type, color);
}

void OpenGL::colorP4uiv(std::uint32_t type, std::uint32_t const* color) {
    _current();
    boom::glColorP4uiv(type, color);
}

void OpenGL::secondaryColorP3ui(std::uint32_t type, std::uint32_t color) {
    _current();
    boom::glSecondaryColorP3ui(type, color);
}

void OpenGL::secondaryColorP3uiv(std::uint32_t type, std::uint32_t const* color) {
    _current();
    boom::glSecondaryColorP3uiv(type, color);
}

void OpenGL::minSampleShading(float value) {
    _current();
    boom::glMinSampleShading(value);
}

void OpenGL::blendEquationi(std::uint32_t buf, std::uint32_t mode) {
    _current();
    boom::glBlendEquationi(buf, mode);
}

void OpenGL::blendEquationSeparatei(std::uint32_t buf, std::uint32_t modeRGB, std::uint32_t modeAlpha) {
    _current();
    boom::glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
}

void OpenGL::blendFunci(std::uint32_t buf, std::uint32_t src, std::uint32_t dst) {
    _current();
    boom::glBlendFunci(buf, src, dst);
}

void OpenGL::blendFuncSeparatei(std::uint32_t buf, std::uint32_t srcRGB, std::uint32_t dstRGB, std::uint32_t srcAlpha, std::uint32_t dstAlpha) {
    _current();
    boom::glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void OpenGL::drawArraysIndirect(std::uint32_t mode, void const* indirect) {
    _current();
    boom::glDrawArraysIndirect(mode, indirect);
}

void OpenGL::drawElementsIndirect(std::uint32_t mode, std::uint32_t type, void const* indirect) {
    _current();
    boom::glDrawElementsIndirect(mode, type, indirect);
}

void OpenGL::uniform1d(std::int32_t location, double x) {
    _current();
    boom::glUniform1d(location, x);
}

void OpenGL::uniform2d(std::int32_t location, double x, double y) {
    _current();
    boom::glUniform2d(location, x, y);
}

void OpenGL::uniform3d(std::int32_t location, double x, double y, double z) {
    _current();
    boom::glUniform3d(location, x, y, z);
}

void OpenGL::uniform4d(std::int32_t location, double x, double y, double z, double w) {
    _current();
    boom::glUniform4d(location, x, y, z, w);
}

void OpenGL::uniform1dv(std::int32_t location, std::int32_t count, double const* value) {
    _current();
    boom::glUniform1dv(location, count, value);
}

void OpenGL::uniform2dv(std::int32_t location, std::int32_t count, double const* value) {
    _current();
    boom::glUniform2dv(location, count, value);
}

void OpenGL::uniform3dv(std::int32_t location, std::int32_t count, double const* value) {
    _current();
    boom::glUniform3dv(location, count, value);
}

void OpenGL::uniform4dv(std::int32_t location, std::int32_t count, double const* value) {
    _current();
    boom::glUniform4dv(location, count, value);
}

void OpenGL::uniformMatrix2dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glUniformMatrix2dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glUniformMatrix3dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glUniformMatrix4dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix2x3dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glUniformMatrix2x3dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix2x4dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glUniformMatrix2x4dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3x2dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glUniformMatrix3x2dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3x4dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glUniformMatrix3x4dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4x2dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glUniformMatrix4x2dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4x3dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glUniformMatrix4x3dv(location, count, transpose, value);
}

void OpenGL::getUniformdv(std::uint32_t program, std::int32_t location, double* params) {
    _current();
    boom::glGetUniformdv(program, location, params);
}

void OpenGL::getActiveSubroutineUniformiv(std::uint32_t program, std::uint32_t shadertype, std::uint32_t index, std::uint32_t pname, std::int32_t* values) {
    _current();
    boom::glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
}

void OpenGL::getActiveSubroutineUniformName(std::uint32_t program, std::uint32_t shadertype, std::uint32_t index, std::int32_t bufSize, std::int32_t* length, char* name) {
    _current();
    boom::glGetActiveSubroutineUniformName(program, shadertype, index, bufSize, length, name);
}

void OpenGL::getActiveSubroutineName(std::uint32_t program, std::uint32_t shadertype, std::uint32_t index, std::int32_t bufSize, std::int32_t* length, char* name) {
    _current();
    boom::glGetActiveSubroutineName(program, shadertype, index, bufSize, length, name);
}

void OpenGL::uniformSubroutinesuiv(std::uint32_t shadertype, std::int32_t count, std::uint32_t const* indices) {
    _current();
    boom::glUniformSubroutinesuiv(shadertype, count, indices);
}

void OpenGL::getUniformSubroutineuiv(std::uint32_t shadertype, std::int32_t location, std::uint32_t* params) {
    _current();
    boom::glGetUniformSubroutineuiv(shadertype, location, params);
}

void OpenGL::getProgramStageiv(std::uint32_t program, std::uint32_t shadertype, std::uint32_t pname, std::int32_t* values) {
    _current();
    boom::glGetProgramStageiv(program, shadertype, pname, values);
}

void OpenGL::patchParameteri(std::uint32_t pname, std::int32_t value) {
    _current();
    boom::glPatchParameteri(pname, value);
}

void OpenGL::patchParameterfv(std::uint32_t pname, float const* values) {
    _current();
    boom::glPatchParameterfv(pname, values);
}

void OpenGL::bindTransformFeedback(std::uint32_t target, std::uint32_t id) {
    _current();
    boom::glBindTransformFeedback(target, id);
}

void OpenGL::deleteTransformFeedbacks(std::int32_t n, std::uint32_t const* ids) {
    _current();
    boom::glDeleteTransformFeedbacks(n, ids);
}

void OpenGL::genTransformFeedbacks(std::int32_t n, std::uint32_t* ids) {
    _current();
    boom::glGenTransformFeedbacks(n, ids);
}

void OpenGL::pauseTransformFeedback() {
    _current();
    boom::glPauseTransformFeedback();
}

void OpenGL::resumeTransformFeedback() {
    _current();
    boom::glResumeTransformFeedback();
}

void OpenGL::drawTransformFeedback(std::uint32_t mode, std::uint32_t id) {
    _current();
    boom::glDrawTransformFeedback(mode, id);
}

void OpenGL::drawTransformFeedbackStream(std::uint32_t mode, std::uint32_t id, std::uint32_t stream) {
    _current();
    boom::glDrawTransformFeedbackStream(mode, id, stream);
}

void OpenGL::beginQueryIndexed(std::uint32_t target, std::uint32_t index, std::uint32_t id) {
    _current();
    boom::glBeginQueryIndexed(target, index, id);
}

void OpenGL::endQueryIndexed(std::uint32_t target, std::uint32_t index) {
    _current();
    boom::glEndQueryIndexed(target, index);
}

void OpenGL::getQueryIndexediv(std::uint32_t target, std::uint32_t index, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetQueryIndexediv(target, index, pname, params);
}

void OpenGL::releaseShaderCompiler() {
    _current();
    boom::glReleaseShaderCompiler();
}

void OpenGL::shaderBinary(std::int32_t count, std::uint32_t const* shaders, std::uint32_t binaryFormat, void const* binary, std::int32_t length) {
    _current();
    boom::glShaderBinary(count, shaders, binaryFormat, binary, length);
}

void OpenGL::getShaderPrecisionFormat(std::uint32_t shadertype, std::uint32_t precisiontype, std::int32_t* range, std::int32_t* precision) {
    _current();
    boom::glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

void OpenGL::depthRangef(float n, float f) {
    _current();
    boom::glDepthRangef(n, f);
}

void OpenGL::clearDepthf(float d) {
    _current();
    boom::glClearDepthf(d);
}

void OpenGL::getProgramBinary(std::uint32_t program, std::int32_t bufSize, std::int32_t* length, std::uint32_t* binaryFormat, void* binary) {
    _current();
    boom::glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
}

void OpenGL::programBinary(std::uint32_t program, std::uint32_t binaryFormat, void const* binary, std::int32_t length) {
    _current();
    boom::glProgramBinary(program, binaryFormat, binary, length);
}

void OpenGL::programParameteri(std::uint32_t program, std::uint32_t pname, std::int32_t value) {
    _current();
    boom::glProgramParameteri(program, pname, value);
}

void OpenGL::useProgramStages(std::uint32_t pipeline, std::uint32_t stages, std::uint32_t program) {
    _current();
    boom::glUseProgramStages(pipeline, stages, program);
}

void OpenGL::activeShaderProgram(std::uint32_t pipeline, std::uint32_t program) {
    _current();
    boom::glActiveShaderProgram(pipeline, program);
}

void OpenGL::bindProgramPipeline(std::uint32_t pipeline) {
    _current();
    boom::glBindProgramPipeline(pipeline);
}

void OpenGL::deleteProgramPipelines(std::int32_t n, std::uint32_t const* pipelines) {
    _current();
    boom::glDeleteProgramPipelines(n, pipelines);
}

void OpenGL::genProgramPipelines(std::int32_t n, std::uint32_t* pipelines) {
    _current();
    boom::glGenProgramPipelines(n, pipelines);
}

void OpenGL::getProgramPipelineiv(std::uint32_t pipeline, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetProgramPipelineiv(pipeline, pname, params);
}

void OpenGL::programUniform1i(std::uint32_t program, std::int32_t location, std::int32_t v0) {
    _current();
    boom::glProgramUniform1i(program, location, v0);
}

void OpenGL::programUniform1iv(std::uint32_t program, std::int32_t location, std::int32_t count, std::int32_t const* value) {
    _current();
    boom::glProgramUniform1iv(program, location, count, value);
}

void OpenGL::programUniform1f(std::uint32_t program, std::int32_t location, float v0) {
    _current();
    boom::glProgramUniform1f(program, location, v0);
}

void OpenGL::programUniform1fv(std::uint32_t program, std::int32_t location, std::int32_t count, float const* value) {
    _current();
    boom::glProgramUniform1fv(program, location, count, value);
}

void OpenGL::programUniform1d(std::uint32_t program, std::int32_t location, double v0) {
    _current();
    boom::glProgramUniform1d(program, location, v0);
}

void OpenGL::programUniform1dv(std::uint32_t program, std::int32_t location, std::int32_t count, double const* value) {
    _current();
    boom::glProgramUniform1dv(program, location, count, value);
}

void OpenGL::programUniform1ui(std::uint32_t program, std::int32_t location, std::uint32_t v0) {
    _current();
    boom::glProgramUniform1ui(program, location, v0);
}

void OpenGL::programUniform1uiv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint32_t const* value) {
    _current();
    boom::glProgramUniform1uiv(program, location, count, value);
}

void OpenGL::programUniform2i(std::uint32_t program, std::int32_t location, std::int32_t v0, std::int32_t v1) {
    _current();
    boom::glProgramUniform2i(program, location, v0, v1);
}

void OpenGL::programUniform2iv(std::uint32_t program, std::int32_t location, std::int32_t count, std::int32_t const* value) {
    _current();
    boom::glProgramUniform2iv(program, location, count, value);
}

void OpenGL::programUniform2f(std::uint32_t program, std::int32_t location, float v0, float v1) {
    _current();
    boom::glProgramUniform2f(program, location, v0, v1);
}

void OpenGL::programUniform2fv(std::uint32_t program, std::int32_t location, std::int32_t count, float const* value) {
    _current();
    boom::glProgramUniform2fv(program, location, count, value);
}

void OpenGL::programUniform2d(std::uint32_t program, std::int32_t location, double v0, double v1) {
    _current();
    boom::glProgramUniform2d(program, location, v0, v1);
}

void OpenGL::programUniform2dv(std::uint32_t program, std::int32_t location, std::int32_t count, double const* value) {
    _current();
    boom::glProgramUniform2dv(program, location, count, value);
}

void OpenGL::programUniform2ui(std::uint32_t program, std::int32_t location, std::uint32_t v0, std::uint32_t v1) {
    _current();
    boom::glProgramUniform2ui(program, location, v0, v1);
}

void OpenGL::programUniform2uiv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint32_t const* value) {
    _current();
    boom::glProgramUniform2uiv(program, location, count, value);
}

void OpenGL::programUniform3i(std::uint32_t program, std::int32_t location, std::int32_t v0, std::int32_t v1, std::int32_t v2) {
    _current();
    boom::glProgramUniform3i(program, location, v0, v1, v2);
}

void OpenGL::programUniform3iv(std::uint32_t program, std::int32_t location, std::int32_t count, std::int32_t const* value) {
    _current();
    boom::glProgramUniform3iv(program, location, count, value);
}

void OpenGL::programUniform3f(std::uint32_t program, std::int32_t location, float v0, float v1, float v2) {
    _current();
    boom::glProgramUniform3f(program, location, v0, v1, v2);
}

void OpenGL::programUniform3fv(std::uint32_t program, std::int32_t location, std::int32_t count, float const* value) {
    _current();
    boom::glProgramUniform3fv(program, location, count, value);
}

void OpenGL::programUniform3d(std::uint32_t program, std::int32_t location, double v0, double v1, double v2) {
    _current();
    boom::glProgramUniform3d(program, location, v0, v1, v2);
}

void OpenGL::programUniform3dv(std::uint32_t program, std::int32_t location, std::int32_t count, double const* value) {
    _current();
    boom::glProgramUniform3dv(program, location, count, value);
}

void OpenGL::programUniform3ui(std::uint32_t program, std::int32_t location, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2) {
    _current();
    boom::glProgramUniform3ui(program, location, v0, v1, v2);
}

void OpenGL::programUniform3uiv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint32_t const* value) {
    _current();
    boom::glProgramUniform3uiv(program, location, count, value);
}

void OpenGL::programUniform4i(std::uint32_t program, std::int32_t location, std::int32_t v0, std::int32_t v1, std::int32_t v2, std::int32_t v3) {
    _current();
    boom::glProgramUniform4i(program, location, v0, v1, v2, v3);
}

void OpenGL::programUniform4iv(std::uint32_t program, std::int32_t location, std::int32_t count, std::int32_t const* value) {
    _current();
    boom::glProgramUniform4iv(program, location, count, value);
}

void OpenGL::programUniform4f(std::uint32_t program, std::int32_t location, float v0, float v1, float v2, float v3) {
    _current();
    boom::glProgramUniform4f(program, location, v0, v1, v2, v3);
}

void OpenGL::programUniform4fv(std::uint32_t program, std::int32_t location, std::int32_t count, float const* value) {
    _current();
    boom::glProgramUniform4fv(program, location, count, value);
}

void OpenGL::programUniform4d(std::uint32_t program, std::int32_t location, double v0, double v1, double v2, double v3) {
    _current();
    boom::glProgramUniform4d(program, location, v0, v1, v2, v3);
}

void OpenGL::programUniform4dv(std::uint32_t program, std::int32_t location, std::int32_t count, double const* value) {
    _current();
    boom::glProgramUniform4dv(program, location, count, value);
}

void OpenGL::programUniform4ui(std::uint32_t program, std::int32_t location, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3) {
    _current();
    boom::glProgramUniform4ui(program, location, v0, v1, v2, v3);
}

void OpenGL::programUniform4uiv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint32_t const* value) {
    _current();
    boom::glProgramUniform4uiv(program, location, count, value);
}

void OpenGL::programUniformMatrix2fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glProgramUniformMatrix2fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glProgramUniformMatrix3fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glProgramUniformMatrix4fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glProgramUniformMatrix2dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glProgramUniformMatrix3dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glProgramUniformMatrix4dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2x3fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3x2fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2x4fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4x2fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3x4fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4x3fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const* value) {
    _current();
    boom::glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2x3dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glProgramUniformMatrix2x3dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3x2dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glProgramUniformMatrix3x2dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2x4dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glProgramUniformMatrix2x4dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4x2dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glProgramUniformMatrix4x2dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3x4dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glProgramUniformMatrix3x4dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4x3dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const* value) {
    _current();
    boom::glProgramUniformMatrix4x3dv(program, location, count, transpose, value);
}

void OpenGL::validateProgramPipeline(std::uint32_t pipeline) {
    _current();
    boom::glValidateProgramPipeline(pipeline);
}

void OpenGL::getProgramPipelineInfoLog(std::uint32_t pipeline, std::int32_t bufSize, std::int32_t* length, char* infoLog) {
    _current();
    boom::glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
}

void OpenGL::vertexAttribL1d(std::uint32_t index, double x) {
    _current();
    boom::glVertexAttribL1d(index, x);
}

void OpenGL::vertexAttribL2d(std::uint32_t index, double x, double y) {
    _current();
    boom::glVertexAttribL2d(index, x, y);
}

void OpenGL::vertexAttribL3d(std::uint32_t index, double x, double y, double z) {
    _current();
    boom::glVertexAttribL3d(index, x, y, z);
}

void OpenGL::vertexAttribL4d(std::uint32_t index, double x, double y, double z, double w) {
    _current();
    boom::glVertexAttribL4d(index, x, y, z, w);
}

void OpenGL::vertexAttribL1dv(std::uint32_t index, double const* v) {
    _current();
    boom::glVertexAttribL1dv(index, v);
}

void OpenGL::vertexAttribL2dv(std::uint32_t index, double const* v) {
    _current();
    boom::glVertexAttribL2dv(index, v);
}

void OpenGL::vertexAttribL3dv(std::uint32_t index, double const* v) {
    _current();
    boom::glVertexAttribL3dv(index, v);
}

void OpenGL::vertexAttribL4dv(std::uint32_t index, double const* v) {
    _current();
    boom::glVertexAttribL4dv(index, v);
}

void OpenGL::vertexAttribLPointer(std::uint32_t index, std::int32_t size, std::uint32_t type, std::int32_t stride, void const* pointer) {
    _current();
    boom::glVertexAttribLPointer(index, size, type, stride, pointer);
}

void OpenGL::getVertexAttribLdv(std::uint32_t index, std::uint32_t pname, double* params) {
    _current();
    boom::glGetVertexAttribLdv(index, pname, params);
}

void OpenGL::viewportArrayv(std::uint32_t first, std::int32_t count, float const* v) {
    _current();
    boom::glViewportArrayv(first, count, v);
}

void OpenGL::viewportIndexedf(std::uint32_t index, float x, float y, float w, float h) {
    _current();
    boom::glViewportIndexedf(index, x, y, w, h);
}

void OpenGL::viewportIndexedfv(std::uint32_t index, float const* v) {
    _current();
    boom::glViewportIndexedfv(index, v);
}

void OpenGL::scissorArrayv(std::uint32_t first, std::int32_t count, std::int32_t const* v) {
    _current();
    boom::glScissorArrayv(first, count, v);
}

void OpenGL::scissorIndexed(std::uint32_t index, std::int32_t left, std::int32_t bottom, std::int32_t width, std::int32_t height) {
    _current();
    boom::glScissorIndexed(index, left, bottom, width, height);
}

void OpenGL::scissorIndexedv(std::uint32_t index, std::int32_t const* v) {
    _current();
    boom::glScissorIndexedv(index, v);
}

void OpenGL::depthRangeArrayv(std::uint32_t first, std::int32_t count, double const* v) {
    _current();
    boom::glDepthRangeArrayv(first, count, v);
}

void OpenGL::depthRangeIndexed(std::uint32_t index, double n, double f) {
    _current();
    boom::glDepthRangeIndexed(index, n, f);
}

void OpenGL::getFloati_v(std::uint32_t target, std::uint32_t index, float* data) {
    _current();
    boom::glGetFloati_v(target, index, data);
}

void OpenGL::getDoublei_v(std::uint32_t target, std::uint32_t index, double* data) {
    _current();
    boom::glGetDoublei_v(target, index, data);
}

void OpenGL::drawArraysInstancedBaseInstance(std::uint32_t mode, std::int32_t first, std::int32_t count, std::int32_t instancecount, std::uint32_t baseinstance) {
    _current();
    boom::glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
}

void OpenGL::drawElementsInstancedBaseInstance(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const* indices, std::int32_t instancecount, std::uint32_t baseinstance) {
    _current();
    boom::glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
}

void OpenGL::drawElementsInstancedBaseVertexBaseInstance(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const* indices, std::int32_t instancecount, std::int32_t basevertex, std::uint32_t baseinstance) {
    _current();
    boom::glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
}

void OpenGL::getInternalformativ(std::uint32_t target, std::uint32_t internalformat, std::uint32_t pname, std::int32_t count, std::int32_t* params) {
    _current();
    boom::glGetInternalformativ(target, internalformat, pname, count, params);
}

void OpenGL::getActiveAtomicCounterBufferiv(std::uint32_t program, std::uint32_t bufferIndex, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
}

void OpenGL::bindImageTexture(std::uint32_t unit, std::uint32_t texture, std::int32_t level, std::uint8_t layered, std::int32_t layer, std::uint32_t access, std::uint32_t format) {
    _current();
    boom::glBindImageTexture(unit, texture, level, layered, layer, access, format);
}

void OpenGL::memoryBarrier(std::uint32_t barriers) {
    _current();
    boom::glMemoryBarrier(barriers);
}

void OpenGL::texStorage1D(std::uint32_t target, std::int32_t levels, std::uint32_t internalformat, std::int32_t width) {
    _current();
    boom::glTexStorage1D(target, levels, internalformat, width);
}

void OpenGL::texStorage2D(std::uint32_t target, std::int32_t levels, std::uint32_t internalformat, std::int32_t width, std::int32_t height) {
    _current();
    boom::glTexStorage2D(target, levels, internalformat, width, height);
}

void OpenGL::texStorage3D(std::uint32_t target, std::int32_t levels, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth) {
    _current();
    boom::glTexStorage3D(target, levels, internalformat, width, height, depth);
}

void OpenGL::drawTransformFeedbackInstanced(std::uint32_t mode, std::uint32_t id, std::int32_t instancecount) {
    _current();
    boom::glDrawTransformFeedbackInstanced(mode, id, instancecount);
}

void OpenGL::drawTransformFeedbackStreamInstanced(std::uint32_t mode, std::uint32_t id, std::uint32_t stream, std::int32_t instancecount) {
    _current();
    boom::glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
}

void OpenGL::clearBufferData(std::uint32_t target, std::uint32_t internalformat, std::uint32_t format, std::uint32_t type, void const* data) {
    _current();
    boom::glClearBufferData(target, internalformat, format, type, data);
}

void OpenGL::clearBufferSubData(std::uint32_t target, std::uint32_t internalformat, std::intptr_t offset, std::int64_t size, std::uint32_t format, std::uint32_t type, void const* data) {
    _current();
    boom::glClearBufferSubData(target, internalformat, offset, size, format, type, data);
}

void OpenGL::dispatchCompute(std::uint32_t num_groups_x, std::uint32_t num_groups_y, std::uint32_t num_groups_z) {
    _current();
    boom::glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
}

void OpenGL::dispatchComputeIndirect(std::intptr_t indirect) {
    _current();
    boom::glDispatchComputeIndirect(indirect);
}

void OpenGL::copyImageSubData(std::uint32_t srcName, std::uint32_t srcTarget, std::int32_t srcLevel, std::int32_t srcX, std::int32_t srcY, std::int32_t srcZ, std::uint32_t dstName, std::uint32_t dstTarget, std::int32_t dstLevel, std::int32_t dstX, std::int32_t dstY, std::int32_t dstZ, std::int32_t srcWidth, std::int32_t srcHeight, std::int32_t srcDepth) {
    _current();
    boom::glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

void OpenGL::framebufferParameteri(std::uint32_t target, std::uint32_t pname, std::int32_t param) {
    _current();
    boom::glFramebufferParameteri(target, pname, param);
}

void OpenGL::getFramebufferParameteriv(std::uint32_t target, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetFramebufferParameteriv(target, pname, params);
}

void OpenGL::getInternalformati64v(std::uint32_t target, std::uint32_t internalformat, std::uint32_t pname, std::int32_t count, std::int64_t* params) {
    _current();
    boom::glGetInternalformati64v(target, internalformat, pname, count, params);
}

void OpenGL::invalidateTexSubImage(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth) {
    _current();
    boom::glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
}

void OpenGL::invalidateTexImage(std::uint32_t texture, std::int32_t level) {
    _current();
    boom::glInvalidateTexImage(texture, level);
}

void OpenGL::invalidateBufferSubData(std::uint32_t buffer, std::intptr_t offset, std::int64_t length) {
    _current();
    boom::glInvalidateBufferSubData(buffer, offset, length);
}

void OpenGL::invalidateBufferData(std::uint32_t buffer) {
    _current();
    boom::glInvalidateBufferData(buffer);
}

void OpenGL::invalidateFramebuffer(std::uint32_t target, std::int32_t numAttachments, std::uint32_t const* attachments) {
    _current();
    boom::glInvalidateFramebuffer(target, numAttachments, attachments);
}

void OpenGL::invalidateSubFramebuffer(std::uint32_t target, std::int32_t numAttachments, std::uint32_t const* attachments, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
    _current();
    boom::glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
}

void OpenGL::multiDrawArraysIndirect(std::uint32_t mode, void const* indirect, std::int32_t drawcount, std::int32_t stride) {
    _current();
    boom::glMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
}

void OpenGL::multiDrawElementsIndirect(std::uint32_t mode, std::uint32_t type, void const* indirect, std::int32_t drawcount, std::int32_t stride) {
    _current();
    boom::glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
}

void OpenGL::getProgramInterfaceiv(std::uint32_t program, std::uint32_t programInterface, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetProgramInterfaceiv(program, programInterface, pname, params);
}

void OpenGL::getProgramResourceName(std::uint32_t program, std::uint32_t programInterface, std::uint32_t index, std::int32_t bufSize, std::int32_t* length, char* name) {
    _current();
    boom::glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
}

void OpenGL::getProgramResourceiv(std::uint32_t program, std::uint32_t programInterface, std::uint32_t index, std::int32_t propCount, std::uint32_t const* props, std::int32_t count, std::int32_t* length, std::int32_t* params) {
    _current();
    boom::glGetProgramResourceiv(program, programInterface, index, propCount, props, count, length, params);
}

void OpenGL::shaderStorageBlockBinding(std::uint32_t program, std::uint32_t storageBlockIndex, std::uint32_t storageBlockBinding) {
    _current();
    boom::glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
}

void OpenGL::texBufferRange(std::uint32_t target, std::uint32_t internalformat, std::uint32_t buffer, std::intptr_t offset, std::int64_t size) {
    _current();
    boom::glTexBufferRange(target, internalformat, buffer, offset, size);
}

void OpenGL::texStorage2DMultisample(std::uint32_t target, std::int32_t samples, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::uint8_t fixedsamplelocations) {
    _current();
    boom::glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

void OpenGL::texStorage3DMultisample(std::uint32_t target, std::int32_t samples, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint8_t fixedsamplelocations) {
    _current();
    boom::glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

void OpenGL::textureView(std::uint32_t texture, std::uint32_t target, std::uint32_t origtexture, std::uint32_t internalformat, std::uint32_t minlevel, std::uint32_t numlevels, std::uint32_t minlayer, std::uint32_t numlayers) {
    _current();
    boom::glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
}

void OpenGL::bindVertexBuffer(std::uint32_t bindingindex, std::uint32_t buffer, std::intptr_t offset, std::int32_t stride) {
    _current();
    boom::glBindVertexBuffer(bindingindex, buffer, offset, stride);
}

void OpenGL::vertexAttribFormat(std::uint32_t attribindex, std::int32_t size, std::uint32_t type, std::uint8_t normalized, std::uint32_t relativeoffset) {
    _current();
    boom::glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
}

void OpenGL::vertexAttribIFormat(std::uint32_t attribindex, std::int32_t size, std::uint32_t type, std::uint32_t relativeoffset) {
    _current();
    boom::glVertexAttribIFormat(attribindex, size, type, relativeoffset);
}

void OpenGL::vertexAttribLFormat(std::uint32_t attribindex, std::int32_t size, std::uint32_t type, std::uint32_t relativeoffset) {
    _current();
    boom::glVertexAttribLFormat(attribindex, size, type, relativeoffset);
}

void OpenGL::vertexAttribBinding(std::uint32_t attribindex, std::uint32_t bindingindex) {
    _current();
    boom::glVertexAttribBinding(attribindex, bindingindex);
}

void OpenGL::vertexBindingDivisor(std::uint32_t bindingindex, std::uint32_t divisor) {
    _current();
    boom::glVertexBindingDivisor(bindingindex, divisor);
}

void OpenGL::debugMessageControl(std::uint32_t source, std::uint32_t type, std::uint32_t severity, std::int32_t count, std::uint32_t const* ids, std::uint8_t enabled) {
    _current();
    boom::glDebugMessageControl(source, type, severity, count, ids, enabled);
}

void OpenGL::debugMessageInsert(std::uint32_t source, std::uint32_t type, std::uint32_t id, std::uint32_t severity, std::int32_t length, char const* buf) {
    _current();
    boom::glDebugMessageInsert(source, type, id, severity, length, buf);
}

void OpenGL::debugMessageCallback(void* callback, void const* userParam) {
    _current();
    boom::glDebugMessageCallback(callback, userParam);
}

void OpenGL::pushDebugGroup(std::uint32_t source, std::uint32_t id, std::int32_t length, char const* message) {
    _current();
    boom::glPushDebugGroup(source, id, length, message);
}

void OpenGL::popDebugGroup() {
    _current();
    boom::glPopDebugGroup();
}

void OpenGL::objectLabel(std::uint32_t identifier, std::uint32_t name, std::int32_t length, char const* label) {
    _current();
    boom::glObjectLabel(identifier, name, length, label);
}

void OpenGL::getObjectLabel(std::uint32_t identifier, std::uint32_t name, std::int32_t bufSize, std::int32_t* length, char* label) {
    _current();
    boom::glGetObjectLabel(identifier, name, bufSize, length, label);
}

void OpenGL::objectPtrLabel(void const* ptr, std::int32_t length, char const* label) {
    _current();
    boom::glObjectPtrLabel(ptr, length, label);
}

void OpenGL::getObjectPtrLabel(void const* ptr, std::int32_t bufSize, std::int32_t* length, char* label) {
    _current();
    boom::glGetObjectPtrLabel(ptr, bufSize, length, label);
}

void OpenGL::getPointerv(std::uint32_t pname, void** params) {
    _current();
    boom::glGetPointerv(pname, params);
}

void OpenGL::bufferStorage(std::uint32_t target, std::int64_t size, void const* data, std::uint32_t flags) {
    _current();
    boom::glBufferStorage(target, size, data, flags);
}

void OpenGL::clearTexImage(std::uint32_t texture, std::int32_t level, std::uint32_t format, std::uint32_t type, void const* data) {
    _current();
    boom::glClearTexImage(texture, level, format, type, data);
}

void OpenGL::clearTexSubImage(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint32_t format, std::uint32_t type, void const* data) {
    _current();
    boom::glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
}

void OpenGL::bindBuffersBase(std::uint32_t target, std::uint32_t first, std::int32_t count, std::uint32_t const* buffers) {
    _current();
    boom::glBindBuffersBase(target, first, count, buffers);
}

void OpenGL::bindBuffersRange(std::uint32_t target, std::uint32_t first, std::int32_t count, std::uint32_t const* buffers, std::intptr_t const* offsets, std::int64_t const* sizes) {
    _current();
    boom::glBindBuffersRange(target, first, count, buffers, offsets, sizes);
}

void OpenGL::bindTextures(std::uint32_t first, std::int32_t count, std::uint32_t const* textures) {
    _current();
    boom::glBindTextures(first, count, textures);
}

void OpenGL::bindSamplers(std::uint32_t first, std::int32_t count, std::uint32_t const* samplers) {
    _current();
    boom::glBindSamplers(first, count, samplers);
}

void OpenGL::bindImageTextures(std::uint32_t first, std::int32_t count, std::uint32_t const* textures) {
    _current();
    boom::glBindImageTextures(first, count, textures);
}

void OpenGL::bindVertexBuffers(std::uint32_t first, std::int32_t count, std::uint32_t const* buffers, std::intptr_t const* offsets, std::int32_t const* strides) {
    _current();
    boom::glBindVertexBuffers(first, count, buffers, offsets, strides);
}

void OpenGL::clipControl(std::uint32_t origin, std::uint32_t depth) {
    _current();
    boom::glClipControl(origin, depth);
}

void OpenGL::createTransformFeedbacks(std::int32_t n, std::uint32_t* ids) {
    _current();
    boom::glCreateTransformFeedbacks(n, ids);
}

void OpenGL::transformFeedbackBufferBase(std::uint32_t xfb, std::uint32_t index, std::uint32_t buffer) {
    _current();
    boom::glTransformFeedbackBufferBase(xfb, index, buffer);
}

void OpenGL::transformFeedbackBufferRange(std::uint32_t xfb, std::uint32_t index, std::uint32_t buffer, std::intptr_t offset, std::int64_t size) {
    _current();
    boom::glTransformFeedbackBufferRange(xfb, index, buffer, offset, size);
}

void OpenGL::getTransformFeedbackiv(std::uint32_t xfb, std::uint32_t pname, std::int32_t* param) {
    _current();
    boom::glGetTransformFeedbackiv(xfb, pname, param);
}

void OpenGL::getTransformFeedbacki_v(std::uint32_t xfb, std::uint32_t pname, std::uint32_t index, std::int32_t* param) {
    _current();
    boom::glGetTransformFeedbacki_v(xfb, pname, index, param);
}

void OpenGL::getTransformFeedbacki64_v(std::uint32_t xfb, std::uint32_t pname, std::uint32_t index, std::int64_t* param) {
    _current();
    boom::glGetTransformFeedbacki64_v(xfb, pname, index, param);
}

void OpenGL::createBuffers(std::int32_t n, std::uint32_t* buffers) {
    _current();
    boom::glCreateBuffers(n, buffers);
}

void OpenGL::namedBufferStorage(std::uint32_t buffer, std::int64_t size, void const* data, std::uint32_t flags) {
    _current();
    boom::glNamedBufferStorage(buffer, size, data, flags);
}

void OpenGL::namedBufferData(std::uint32_t buffer, std::int64_t size, void const* data, std::uint32_t usage) {
    _current();
    boom::glNamedBufferData(buffer, size, data, usage);
}

void OpenGL::namedBufferSubData(std::uint32_t buffer, std::intptr_t offset, std::int64_t size, void const* data) {
    _current();
    boom::glNamedBufferSubData(buffer, offset, size, data);
}

void OpenGL::copyNamedBufferSubData(std::uint32_t readBuffer, std::uint32_t writeBuffer, std::intptr_t readOffset, std::intptr_t writeOffset, std::int64_t size) {
    _current();
    boom::glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
}

void OpenGL::clearNamedBufferData(std::uint32_t buffer, std::uint32_t internalformat, std::uint32_t format, std::uint32_t type, void const* data) {
    _current();
    boom::glClearNamedBufferData(buffer, internalformat, format, type, data);
}

void OpenGL::clearNamedBufferSubData(std::uint32_t buffer, std::uint32_t internalformat, std::intptr_t offset, std::int64_t size, std::uint32_t format, std::uint32_t type, void const* data) {
    _current();
    boom::glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
}

void OpenGL::flushMappedNamedBufferRange(std::uint32_t buffer, std::intptr_t offset, std::int64_t length) {
    _current();
    boom::glFlushMappedNamedBufferRange(buffer, offset, length);
}

void OpenGL::getNamedBufferParameteriv(std::uint32_t buffer, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetNamedBufferParameteriv(buffer, pname, params);
}

void OpenGL::getNamedBufferParameteri64v(std::uint32_t buffer, std::uint32_t pname, std::int64_t* params) {
    _current();
    boom::glGetNamedBufferParameteri64v(buffer, pname, params);
}

void OpenGL::getNamedBufferPointerv(std::uint32_t buffer, std::uint32_t pname, void** params) {
    _current();
    boom::glGetNamedBufferPointerv(buffer, pname, params);
}

void OpenGL::getNamedBufferSubData(std::uint32_t buffer, std::intptr_t offset, std::int64_t size, void* data) {
    _current();
    boom::glGetNamedBufferSubData(buffer, offset, size, data);
}

void OpenGL::createFramebuffers(std::int32_t n, std::uint32_t* framebuffers) {
    _current();
    boom::glCreateFramebuffers(n, framebuffers);
}

void OpenGL::namedFramebufferRenderbuffer(std::uint32_t framebuffer, std::uint32_t attachment, std::uint32_t renderbuffertarget, std::uint32_t renderbuffer) {
    _current();
    boom::glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
}

void OpenGL::namedFramebufferParameteri(std::uint32_t framebuffer, std::uint32_t pname, std::int32_t param) {
    _current();
    boom::glNamedFramebufferParameteri(framebuffer, pname, param);
}

void OpenGL::namedFramebufferTexture(std::uint32_t framebuffer, std::uint32_t attachment, std::uint32_t texture, std::int32_t level) {
    _current();
    boom::glNamedFramebufferTexture(framebuffer, attachment, texture, level);
}

void OpenGL::namedFramebufferTextureLayer(std::uint32_t framebuffer, std::uint32_t attachment, std::uint32_t texture, std::int32_t level, std::int32_t layer) {
    _current();
    boom::glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
}

void OpenGL::namedFramebufferDrawBuffer(std::uint32_t framebuffer, std::uint32_t buf) {
    _current();
    boom::glNamedFramebufferDrawBuffer(framebuffer, buf);
}

void OpenGL::namedFramebufferDrawBuffers(std::uint32_t framebuffer, std::int32_t n, std::uint32_t const* bufs) {
    _current();
    boom::glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
}

void OpenGL::namedFramebufferReadBuffer(std::uint32_t framebuffer, std::uint32_t src) {
    _current();
    boom::glNamedFramebufferReadBuffer(framebuffer, src);
}

void OpenGL::invalidateNamedFramebufferData(std::uint32_t framebuffer, std::int32_t numAttachments, std::uint32_t const* attachments) {
    _current();
    boom::glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
}

void OpenGL::invalidateNamedFramebufferSubData(std::uint32_t framebuffer, std::int32_t numAttachments, std::uint32_t const* attachments, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
    _current();
    boom::glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
}

void OpenGL::clearNamedFramebufferiv(std::uint32_t framebuffer, std::uint32_t buffer, std::int32_t drawbuffer, std::int32_t const* value) {
    _current();
    boom::glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
}

void OpenGL::clearNamedFramebufferuiv(std::uint32_t framebuffer, std::uint32_t buffer, std::int32_t drawbuffer, std::uint32_t const* value) {
    _current();
    boom::glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
}

void OpenGL::clearNamedFramebufferfv(std::uint32_t framebuffer, std::uint32_t buffer, std::int32_t drawbuffer, float const* value) {
    _current();
    boom::glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
}

void OpenGL::clearNamedFramebufferfi(std::uint32_t framebuffer, std::uint32_t buffer, std::int32_t drawbuffer, float depth, std::int32_t stencil) {
    _current();
    boom::glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
}

void OpenGL::blitNamedFramebuffer(std::uint32_t readFramebuffer, std::uint32_t drawFramebuffer, std::int32_t srcX0, std::int32_t srcY0, std::int32_t srcX1, std::int32_t srcY1, std::int32_t dstX0, std::int32_t dstY0, std::int32_t dstX1, std::int32_t dstY1, std::uint32_t mask, std::uint32_t filter) {
    _current();
    boom::glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void OpenGL::getNamedFramebufferParameteriv(std::uint32_t framebuffer, std::uint32_t pname, std::int32_t* param) {
    _current();
    boom::glGetNamedFramebufferParameteriv(framebuffer, pname, param);
}

void OpenGL::getNamedFramebufferAttachmentParameteriv(std::uint32_t framebuffer, std::uint32_t attachment, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
}

void OpenGL::createRenderbuffers(std::int32_t n, std::uint32_t* renderbuffers) {
    _current();
    boom::glCreateRenderbuffers(n, renderbuffers);
}

void OpenGL::namedRenderbufferStorage(std::uint32_t renderbuffer, std::uint32_t internalformat, std::int32_t width, std::int32_t height) {
    _current();
    boom::glNamedRenderbufferStorage(renderbuffer, internalformat, width, height);
}

void OpenGL::namedRenderbufferStorageMultisample(std::uint32_t renderbuffer, std::int32_t samples, std::uint32_t internalformat, std::int32_t width, std::int32_t height) {
    _current();
    boom::glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
}

void OpenGL::getNamedRenderbufferParameteriv(std::uint32_t renderbuffer, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetNamedRenderbufferParameteriv(renderbuffer, pname, params);
}

void OpenGL::createTextures(std::uint32_t target, std::int32_t n, std::uint32_t* textures) {
    _current();
    boom::glCreateTextures(target, n, textures);
}

void OpenGL::textureBuffer(std::uint32_t texture, std::uint32_t internalformat, std::uint32_t buffer) {
    _current();
    boom::glTextureBuffer(texture, internalformat, buffer);
}

void OpenGL::textureBufferRange(std::uint32_t texture, std::uint32_t internalformat, std::uint32_t buffer, std::intptr_t offset, std::int64_t size) {
    _current();
    boom::glTextureBufferRange(texture, internalformat, buffer, offset, size);
}

void OpenGL::textureStorage1D(std::uint32_t texture, std::int32_t levels, std::uint32_t internalformat, std::int32_t width) {
    _current();
    boom::glTextureStorage1D(texture, levels, internalformat, width);
}

void OpenGL::textureStorage2D(std::uint32_t texture, std::int32_t levels, std::uint32_t internalformat, std::int32_t width, std::int32_t height) {
    _current();
    boom::glTextureStorage2D(texture, levels, internalformat, width, height);
}

void OpenGL::textureStorage3D(std::uint32_t texture, std::int32_t levels, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth) {
    _current();
    boom::glTextureStorage3D(texture, levels, internalformat, width, height, depth);
}

void OpenGL::textureStorage2DMultisample(std::uint32_t texture, std::int32_t samples, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::uint8_t fixedsamplelocations) {
    _current();
    boom::glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
}

void OpenGL::textureStorage3DMultisample(std::uint32_t texture, std::int32_t samples, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint8_t fixedsamplelocations) {
    _current();
    boom::glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
}

void OpenGL::textureSubImage1D(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t width, std::uint32_t format, std::uint32_t type, void const* pixels) {
    _current();
    boom::glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
}

void OpenGL::textureSubImage2D(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t width, std::int32_t height, std::uint32_t format, std::uint32_t type, void const* pixels) {
    _current();
    boom::glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
}

void OpenGL::textureSubImage3D(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint32_t format, std::uint32_t type, void const* pixels) {
    _current();
    boom::glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void OpenGL::compressedTextureSubImage1D(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t width, std::uint32_t format, std::int32_t imageSize, void const* data) {
    _current();
    boom::glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
}

void OpenGL::compressedTextureSubImage2D(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t width, std::int32_t height, std::uint32_t format, std::int32_t imageSize, void const* data) {
    _current();
    boom::glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void OpenGL::compressedTextureSubImage3D(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint32_t format, std::int32_t imageSize, void const* data) {
    _current();
    boom::glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void OpenGL::copyTextureSubImage1D(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t x, std::int32_t y, std::int32_t width) {
    _current();
    boom::glCopyTextureSubImage1D(texture, level, xoffset, x, y, width);
}

void OpenGL::copyTextureSubImage2D(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
    _current();
    boom::glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
}

void OpenGL::copyTextureSubImage3D(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
    _current();
    boom::glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void OpenGL::textureParameterf(std::uint32_t texture, std::uint32_t pname, float param) {
    _current();
    boom::glTextureParameterf(texture, pname, param);
}

void OpenGL::textureParameterfv(std::uint32_t texture, std::uint32_t pname, float const* param) {
    _current();
    boom::glTextureParameterfv(texture, pname, param);
}

void OpenGL::textureParameteri(std::uint32_t texture, std::uint32_t pname, std::int32_t param) {
    _current();
    boom::glTextureParameteri(texture, pname, param);
}

void OpenGL::textureParameterIiv(std::uint32_t texture, std::uint32_t pname, std::int32_t const* params) {
    _current();
    boom::glTextureParameterIiv(texture, pname, params);
}

void OpenGL::textureParameterIuiv(std::uint32_t texture, std::uint32_t pname, std::uint32_t const* params) {
    _current();
    boom::glTextureParameterIuiv(texture, pname, params);
}

void OpenGL::textureParameteriv(std::uint32_t texture, std::uint32_t pname, std::int32_t const* param) {
    _current();
    boom::glTextureParameteriv(texture, pname, param);
}

void OpenGL::generateTextureMipmap(std::uint32_t texture) {
    _current();
    boom::glGenerateTextureMipmap(texture);
}

void OpenGL::bindTextureUnit(std::uint32_t unit, std::uint32_t texture) {
    _current();
    boom::glBindTextureUnit(unit, texture);
}

void OpenGL::getTextureImage(std::uint32_t texture, std::int32_t level, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void* pixels) {
    _current();
    boom::glGetTextureImage(texture, level, format, type, bufSize, pixels);
}

void OpenGL::getCompressedTextureImage(std::uint32_t texture, std::int32_t level, std::int32_t bufSize, void* pixels) {
    _current();
    boom::glGetCompressedTextureImage(texture, level, bufSize, pixels);
}

void OpenGL::getTextureLevelParameterfv(std::uint32_t texture, std::int32_t level, std::uint32_t pname, float* params) {
    _current();
    boom::glGetTextureLevelParameterfv(texture, level, pname, params);
}

void OpenGL::getTextureLevelParameteriv(std::uint32_t texture, std::int32_t level, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetTextureLevelParameteriv(texture, level, pname, params);
}

void OpenGL::getTextureParameterfv(std::uint32_t texture, std::uint32_t pname, float* params) {
    _current();
    boom::glGetTextureParameterfv(texture, pname, params);
}

void OpenGL::getTextureParameterIiv(std::uint32_t texture, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetTextureParameterIiv(texture, pname, params);
}

void OpenGL::getTextureParameterIuiv(std::uint32_t texture, std::uint32_t pname, std::uint32_t* params) {
    _current();
    boom::glGetTextureParameterIuiv(texture, pname, params);
}

void OpenGL::getTextureParameteriv(std::uint32_t texture, std::uint32_t pname, std::int32_t* params) {
    _current();
    boom::glGetTextureParameteriv(texture, pname, params);
}

void OpenGL::createVertexArrays(std::int32_t n, std::uint32_t* arrays) {
    _current();
    boom::glCreateVertexArrays(n, arrays);
}

void OpenGL::disableVertexArrayAttrib(std::uint32_t vaobj, std::uint32_t index) {
    _current();
    boom::glDisableVertexArrayAttrib(vaobj, index);
}

void OpenGL::enableVertexArrayAttrib(std::uint32_t vaobj, std::uint32_t index) {
    _current();
    boom::glEnableVertexArrayAttrib(vaobj, index);
}

void OpenGL::vertexArrayElementBuffer(std::uint32_t vaobj, std::uint32_t buffer) {
    _current();
    boom::glVertexArrayElementBuffer(vaobj, buffer);
}

void OpenGL::vertexArrayVertexBuffer(std::uint32_t vaobj, std::uint32_t bindingindex, std::uint32_t buffer, std::intptr_t offset, std::int32_t stride) {
    _current();
    boom::glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
}

void OpenGL::vertexArrayVertexBuffers(std::uint32_t vaobj, std::uint32_t first, std::int32_t count, std::uint32_t const* buffers, std::intptr_t const* offsets, std::int32_t const* strides) {
    _current();
    boom::glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
}

void OpenGL::vertexArrayAttribBinding(std::uint32_t vaobj, std::uint32_t attribindex, std::uint32_t bindingindex) {
    _current();
    boom::glVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
}

void OpenGL::vertexArrayAttribFormat(std::uint32_t vaobj, std::uint32_t attribindex, std::int32_t size, std::uint32_t type, std::uint8_t normalized, std::uint32_t relativeoffset) {
    _current();
    boom::glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
}

void OpenGL::vertexArrayAttribIFormat(std::uint32_t vaobj, std::uint32_t attribindex, std::int32_t size, std::uint32_t type, std::uint32_t relativeoffset) {
    _current();
    boom::glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
}

void OpenGL::vertexArrayAttribLFormat(std::uint32_t vaobj, std::uint32_t attribindex, std::int32_t size, std::uint32_t type, std::uint32_t relativeoffset) {
    _current();
    boom::glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
}

void OpenGL::vertexArrayBindingDivisor(std::uint32_t vaobj, std::uint32_t bindingindex, std::uint32_t divisor) {
    _current();
    boom::glVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
}

void OpenGL::getVertexArrayiv(std::uint32_t vaobj, std::uint32_t pname, std::int32_t* param) {
    _current();
    boom::glGetVertexArrayiv(vaobj, pname, param);
}

void OpenGL::getVertexArrayIndexediv(std::uint32_t vaobj, std::uint32_t index, std::uint32_t pname, std::int32_t* param) {
    _current();
    boom::glGetVertexArrayIndexediv(vaobj, index, pname, param);
}

void OpenGL::getVertexArrayIndexed64iv(std::uint32_t vaobj, std::uint32_t index, std::uint32_t pname, std::int64_t* param) {
    _current();
    boom::glGetVertexArrayIndexed64iv(vaobj, index, pname, param);
}

void OpenGL::createSamplers(std::int32_t n, std::uint32_t* samplers) {
    _current();
    boom::glCreateSamplers(n, samplers);
}

void OpenGL::createProgramPipelines(std::int32_t n, std::uint32_t* pipelines) {
    _current();
    boom::glCreateProgramPipelines(n, pipelines);
}

void OpenGL::createQueries(std::uint32_t target, std::int32_t n, std::uint32_t* ids) {
    _current();
    boom::glCreateQueries(target, n, ids);
}

void OpenGL::getQueryBufferObjecti64v(std::uint32_t id, std::uint32_t buffer, std::uint32_t pname, std::intptr_t offset) {
    _current();
    boom::glGetQueryBufferObjecti64v(id, buffer, pname, offset);
}

void OpenGL::getQueryBufferObjectiv(std::uint32_t id, std::uint32_t buffer, std::uint32_t pname, std::intptr_t offset) {
    _current();
    boom::glGetQueryBufferObjectiv(id, buffer, pname, offset);
}

void OpenGL::getQueryBufferObjectui64v(std::uint32_t id, std::uint32_t buffer, std::uint32_t pname, std::intptr_t offset) {
    _current();
    boom::glGetQueryBufferObjectui64v(id, buffer, pname, offset);
}

void OpenGL::getQueryBufferObjectuiv(std::uint32_t id, std::uint32_t buffer, std::uint32_t pname, std::intptr_t offset) {
    _current();
    boom::glGetQueryBufferObjectuiv(id, buffer, pname, offset);
}

void OpenGL::memoryBarrierByRegion(std::uint32_t barriers) {
    _current();
    boom::glMemoryBarrierByRegion(barriers);
}

void OpenGL::getTextureSubImage(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void* pixels) {
    _current();
    boom::glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
}

void OpenGL::getCompressedTextureSubImage(std::uint32_t texture, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth, std::int32_t bufSize, void* pixels) {
    _current();
    boom::glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
}

void OpenGL::getnCompressedTexImage(std::uint32_t target, std::int32_t lod, std::int32_t bufSize, void* pixels) {
    _current();
    boom::glGetnCompressedTexImage(target, lod, bufSize, pixels);
}

void OpenGL::getnTexImage(std::uint32_t target, std::int32_t level, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void* pixels) {
    _current();
    boom::glGetnTexImage(target, level, format, type, bufSize, pixels);
}

void OpenGL::getnUniformdv(std::uint32_t program, std::int32_t location, std::int32_t bufSize, double* params) {
    _current();
    boom::glGetnUniformdv(program, location, bufSize, params);
}

void OpenGL::getnUniformfv(std::uint32_t program, std::int32_t location, std::int32_t bufSize, float* params) {
    _current();
    boom::glGetnUniformfv(program, location, bufSize, params);
}

void OpenGL::getnUniformiv(std::uint32_t program, std::int32_t location, std::int32_t bufSize, std::int32_t* params) {
    _current();
    boom::glGetnUniformiv(program, location, bufSize, params);
}

void OpenGL::getnUniformuiv(std::uint32_t program, std::int32_t location, std::int32_t bufSize, std::uint32_t* params) {
    _current();
    boom::glGetnUniformuiv(program, location, bufSize, params);
}

void OpenGL::readnPixels(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void* data) {
    _current();
    boom::glReadnPixels(x, y, width, height, format, type, bufSize, data);
}

void OpenGL::getnMapdv(std::uint32_t target, std::uint32_t query, std::int32_t bufSize, double* v) {
    _current();
    boom::glGetnMapdv(target, query, bufSize, v);
}

void OpenGL::getnMapfv(std::uint32_t target, std::uint32_t query, std::int32_t bufSize, float* v) {
    _current();
    boom::glGetnMapfv(target, query, bufSize, v);
}

void OpenGL::getnMapiv(std::uint32_t target, std::uint32_t query, std::int32_t bufSize, std::int32_t* v) {
    _current();
    boom::glGetnMapiv(target, query, bufSize, v);
}

void OpenGL::getnPixelMapfv(std::uint32_t map, std::int32_t bufSize, float* values) {
    _current();
    boom::glGetnPixelMapfv(map, bufSize, values);
}

void OpenGL::getnPixelMapuiv(std::uint32_t map, std::int32_t bufSize, std::uint32_t* values) {
    _current();
    boom::glGetnPixelMapuiv(map, bufSize, values);
}

void OpenGL::getnPixelMapusv(std::uint32_t map, std::int32_t bufSize, std::uint16_t* values) {
    _current();
    boom::glGetnPixelMapusv(map, bufSize, values);
}

void OpenGL::getnPolygonStipple(std::int32_t bufSize, std::uint8_t* pattern) {
    _current();
    boom::glGetnPolygonStipple(bufSize, pattern);
}

void OpenGL::getnColorTable(std::uint32_t target, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void* table) {
    _current();
    boom::glGetnColorTable(target, format, type, bufSize, table);
}

void OpenGL::getnConvolutionFilter(std::uint32_t target, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void* image) {
    _current();
    boom::glGetnConvolutionFilter(target, format, type, bufSize, image);
}

void OpenGL::getnSeparableFilter(std::uint32_t target, std::uint32_t format, std::uint32_t type, std::int32_t rowBufSize, void* row, std::int32_t columnBufSize, void* column, void* span) {
    _current();
    boom::glGetnSeparableFilter(target, format, type, rowBufSize, row, columnBufSize, column, span);
}

void OpenGL::getnHistogram(std::uint32_t target, std::uint8_t reset, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void* values) {
    _current();
    boom::glGetnHistogram(target, reset, format, type, bufSize, values);
}

void OpenGL::getnMinmax(std::uint32_t target, std::uint8_t reset, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void* values) {
    _current();
    boom::glGetnMinmax(target, reset, format, type, bufSize, values);
}

void OpenGL::textureBarrier() {
    _current();
    boom::glTextureBarrier();
}

void OpenGL::specializeShader(std::uint32_t shader, char const* pEntryPoint, std::uint32_t numSpecializationConstants, std::uint32_t const* pConstantIndex, std::uint32_t const* pConstantValue) {
    _current();
    boom::glSpecializeShader(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue);
}

void OpenGL::multiDrawArraysIndirectCount(std::uint32_t mode, void const* indirect, std::intptr_t drawcount, std::int32_t maxdrawcount, std::int32_t stride) {
    _current();
    boom::glMultiDrawArraysIndirectCount(mode, indirect, drawcount, maxdrawcount, stride);
}

void OpenGL::multiDrawElementsIndirectCount(std::uint32_t mode, std::uint32_t type, void const* indirect, std::intptr_t drawcount, std::int32_t maxdrawcount, std::int32_t stride) {
    _current();
    boom::glMultiDrawElementsIndirectCount(mode, type, indirect, drawcount, maxdrawcount, stride);
}

void OpenGL::polygonOffsetClamp(float factor, float units, float clamp) {
    _current();
    boom::glPolygonOffsetClamp(factor, units, clamp);
}

void OpenGL::blendBarrier() {
    _current();
    boom::glBlendBarrier();
}

void OpenGL::primitiveBoundingBox(float minX, float minY, float minZ, float minW, float maxX, float maxY, float maxZ, float maxW) {
    _current();
    boom::glPrimitiveBoundingBox(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
}

void OpenGL::swap() {
    _current();
    _implSwap();
}

void OpenGL::_current() {
    _implCurrent();
}

void OpenGL::_bootstrap() {
    _implBootstrap();
}

} /* namespace boom */