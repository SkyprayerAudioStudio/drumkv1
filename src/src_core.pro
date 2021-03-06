# drumkv1.pro
#
NAME = drumkv1

TARGET = $${NAME}
TEMPLATE = lib
CONFIG += static

include(src_core.pri)

HEADERS = \
	config.h \
	drumkv1.h \
	drumkv1_config.h \
	drumkv1_filter.h \
	drumkv1_formant.h \
	drumkv1_resampler.h \
	drumkv1_sample.h \
	drumkv1_wave.h \
	drumkv1_ramp.h \
	drumkv1_list.h \
	drumkv1_fx.h \
	drumkv1_reverb.h \
	drumkv1_param.h \
	drumkv1_sched.h \
	drumkv1_tuning.h \
	drumkv1_programs.h \
	drumkv1_controls.h

SOURCES = \
	drumkv1.cpp \
	drumkv1_config.cpp \
	drumkv1_formant.cpp \
	drumkv1_resampler.cpp \
	drumkv1_sample.cpp \
	drumkv1_wave.cpp \
	drumkv1_param.cpp \
	drumkv1_sched.cpp \
	drumkv1_tuning.cpp \
	drumkv1_programs.cpp \
	drumkv1_controls.cpp


unix {

	OBJECTS_DIR = .obj_core
	MOC_DIR     = .moc_core
	UI_DIR      = .ui_core
}

QT -= gui
QT += xml
