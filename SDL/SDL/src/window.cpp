#include <window.hpp>
#include <cmath>  // للتأكد من أن دالة sin متاحة

namespace Window {
    Window::Window() : window(nullptr), renderer(nullptr), surface(nullptr),
                       textureLeft(nullptr), textureRight(nullptr), currentTexture(nullptr),
                       backgroundTexture(nullptr) {
    }

    bool Window::init() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", language["ERROR_SDL_initialize"].c_str(),
                         SDL_GetError());
            return false;
        }

        if (!SDL_CreateWindowAndRenderer("لعبة", windowWidth, windowHeight, SDL_WINDOW_MAXIMIZED, &window, &renderer)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s: %s", language["ERROR_SDL_initialize"].c_str(),
                         SDL_GetError());
            return false;
        }

        // تحميل صورة الأرنب (يسار)
        surface = SDL_LoadBMP("../images/rabitLeft.bmp");
        if (!surface) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s: %s", language["ERROR_create_surface"].c_str(),
                         SDL_GetError());
            return false;
        }
        textureLeft = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        // تحميل صورة الأرنب (يمين)
        surface = SDL_LoadBMP("../images/rabitRight.bmp");
        if (!surface) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s: %s", language["ERROR_create_surface"].c_str(),
                         SDL_GetError());
            return false;
        }
        textureRight = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        // تعيين الصورة الافتراضية
        currentTexture = textureLeft;

        // تحميل صورة الخلفية
        surface = SDL_LoadBMP("../images/background.bmp");
        if (!surface) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s: %s", language["ERROR_create_surface"].c_str(),
                         SDL_GetError());
            return false;
        }
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        return true;
    }

    void Window::run() {
        SDL_FRect srcRect = {0.0f, 0.0f, 126.0f, 215.0f};
        SDL_FRect dstRect = {550.0f, 450.0f, 126.0f, 215.0f};
        // إضافة متغير جديد لحفظ آخر موقع هبوط للأرنب في المحور Y
        float lastLandingY = dstRect.y;
        // تعيين إحداثيات البداية للخلفية
        float backgroundX1 = 0.01f;
        float backgroundX2 = float(windowWidth); // الخلفية الثانية تبدأ بعد الأولى
        const float backgroundSpeed = 0.01f; // سرعة تحرك الخلفية

        // تعريف المتغيرات الخاصة بالقفز
        float jumpTime = 0.0f; // الوقت الابتدائي للقفز
        float startY = 300.0f; // ارتفاع البداية للأرنب قبل القفز
        bool isJumping = false; // حالة القفز (هل الأرنب في قفز أم لا)
        bool running = true;
        // تعريف متغير ارتفاع القفزة
        float jumpHeightMultiplier = 150.0f; // يمكن تعديله لزيادة أو تقليل ارتفاع القفزة
        // المتغيرات الخاصة بالحركة
        float moveSpeedVertical = 30.0f; // سرعة الحركة الرأسية (للأسهم لأعلى ولأسفل)
        float moveSpeedHorizontal = 30.0f; // سرعة الحركة الأفقية (للأسهم لليمين واليسار)

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT || (
                        event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
                    running = false;
                }

                if (event.type == SDL_EVENT_KEY_DOWN) {
                    // الضغط على مفتاح السهم للأعلى يرفع الأرنب للأعلى بشكل مستمر
                    if (event.key.key == SDLK_UP) {
                        dstRect.y -= moveSpeedVertical; // رفع الأرنب للأعلى تدريجياً
                        startY= dstRect.y;
                    }

                    // الضغط على مفتاح السهم للأسفل لتحريك الأرنب للأسفل
                    if (event.key.key == SDLK_DOWN) {
                        dstRect.y = std::min(dstRect.y + moveSpeedVertical, float(windowHeight) - dstRect.h);
                        startY= dstRect.y;
                    }
                    if (event.key.key == SDLK_UP) {
                        // التأكد من أن الأرنب لن يتجاوز الحد الأعلى للشاشة
                        dstRect.y = std::max(dstRect.y - 10.0f, 0.0f);
                        startY= dstRect.y;
                    }
                    // الضغط على حرف 'r' يؤدي إلى القفز للأمام (إلى اليمين)
                    if (event.key.key == SDLK_R) {
                        // قفز إلى اليمين
                        isJumping = true;
                        jumpTime = 0.0f; // إعادة ضبط وقت القفز
                        currentTexture = textureRight; // تغيير اتجاه الأرنب
                        startY= dstRect.y;
                    }

                    // الضغط على حرف 'w' يؤدي إلى القفز إلى اليسار
                    if (event.key.key == SDLK_W) {
                        // قفز إلى اليسار
                        isJumping = true;
                        jumpTime = 0.0f; // إعادة ضبط وقت القفز
                        currentTexture = textureLeft; // تغيير اتجاه الأرنب
                    }

                    // الضغط على مفتاح السهم الأيسر لتحريك الأرنب إلى اليسار
                    if (event.key.key == SDLK_LEFT) {
                        dstRect.x = std::max(dstRect.x - moveSpeedHorizontal, 0.0f); // لا يتخطى اليسار
                        currentTexture = textureLeft; // تغيير اتجاه الأرنب
                    }

                    // الضغط على مفتاح السهم الأيمن لتحريك الأرنب إلى اليمين
                    if (event.key.key == SDLK_RIGHT) {
                        dstRect.x = std::min(dstRect.x + moveSpeedHorizontal, float(windowWidth) - dstRect.w);
                        // لا يتخطى اليمين
                        currentTexture = textureRight; // تغيير اتجاه الأرنب
                    }
                }
            }

            // معالجة القفز إذا كان الأرنب في حالة قفز
            if (isJumping) {
                // إضافة الحركة الأفقية لمحاكاة القفز
                if (currentTexture == textureRight) {
                    dstRect.x = std::min(dstRect.x + 5.0f, float(windowWidth) - dstRect.w); // القفز إلى اليمين
                } else {
                    dstRect.x = std::max(dstRect.x - 5.0f, 0.0f); // القفز إلى اليسار
                }

                // حساب الارتفاع باستخدام دالة sin لمحاكاة القفز القوسي
                float jumpHeight = std::sin(jumpTime) * jumpHeightMultiplier; // قفز قوسي للأعلى ثم نزول للأسفل
                dstRect.y = std::max(startY - jumpHeight, 0.0f); // تحديد حركة الأرنب على المحور y

                // زيادة jumpTime لمحاكاة القفز تدريجياً
                jumpTime += 0.09f; // يمكنك تعديل هذا الرقم لتغيير سرعة القفز

                // إذا وصل الأرنب إلى قمة القفز (نصف دورة دالة sin)، قم بتغيير اتجاه القفز
                if (jumpTime > 3.14f) {
                    // 2π هو نهاية الدورة الكاملة لدالة sin
                    isJumping = false; // إيقاف القفز عند الهبوط
                    dstRect.y = startY; // إعادة الأرنب إلى ارتفاعه الأصلي
                    lastLandingY = dstRect.y; // حفظ موقع الهبوط الأخير
                }
            }

            // تحديث إحداثيات الخلفية لتحريكها
            backgroundX1 -= backgroundSpeed;
            backgroundX2 -= backgroundSpeed;

            // إذا خرجت الخلفية الأولى خارج الشاشة، نعيدها إلى اليمين
            if (backgroundX1 <= -float(windowWidth)) {
                backgroundX1 = float(windowWidth);
            }

            // إذا خرجت الخلفية الثانية خارج الشاشة، نعيدها إلى اليمين
            if (backgroundX2 <= -float(windowWidth)) {
                backgroundX2 = float(windowWidth);
            }

            // رسم الخلفيتين المتحركتين
            SDL_RenderClear(renderer);

            // الخلفية الأولى
            SDL_FRect backgroundRect1 = {backgroundX1, 0.0f, float(windowWidth), float(windowHeight)};
            SDL_RenderTexture(renderer, backgroundTexture, nullptr, &backgroundRect1);

            // الخلفية الثانية (لملء الفراغ)
            SDL_FRect backgroundRect2 = {backgroundX2, 0.0f, float(windowWidth), float(windowHeight)};
            SDL_RenderTexture(renderer, backgroundTexture, nullptr, &backgroundRect2);

            // رسم الأرنب
            SDL_RenderTexture(renderer, currentTexture, &srcRect, &dstRect);

            SDL_RenderPresent(renderer);
        }
    }

    void Window::cleanUp() {
        SDL_DestroyTexture(textureLeft);
        SDL_DestroyTexture(textureRight);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    Window::~Window() {
        cleanUp();
    }
};
