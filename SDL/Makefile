# اسم البرنامج الداخلي (بدون لاحقة .app)
TARGET = BK

# اسم تطبيق macOS (مع اللاحقة .app)
APP_NAME = $(TARGET).app

# ملفات المصدر الرئيسية
SRC = src/main.cpp
SDL_DIR = sdl

# إعدادات الترجمة مع SDL3
CXX = clang++
CXXFLAGS = -std=c++17 -I$(CURDIR)/include -I$(CURDIR)/$(SDL_DIR)/include -I/usr/local/include
LDFLAGS = -L/usr/local/lib -Wl,-rpath,/usr/local/lib -framework SDL3

# الهدف الأساسي: بناء .app فقط
all:
	@echo "🔧 بناء التطبيق..."
	# بناء التطبيق مباشرة
	$(CXX) $(CXXFLAGS) -o $(SRC) $(LDFLAGS)

# تشغيل التطبيق
run: all
	open "debug/$(APP_NAME)"

# تنظيف التطبيق بالكامل
clean: clean-app clean-build
	@echo "🧹 تم تنظيف التطبيق بالكامل."

# تنظيف مجلد التطبيق فقط
clean-app:
	rm -rf "build"
	@echo "🧹 تم حذف التطبيق فقط."

# تنظيف مجلد البناء المؤقت
clean-build:
	rm -rf "build"
	@echo "🧹 تم حذف مجلد البناء المؤقت."

# هدف تنظيف جميع الملفات وإعادة إنشاء المجلد
cleanall:
	@echo "تنظيف مجلد البناء وإعادة إنشائه..."
	rm -rf "build" # حذف مجلد البناء
	mkdir -p "build" # إعادة إنشاء المجلد
	@echo "✅ تم إعادة إنشاء مجلد البناء."
