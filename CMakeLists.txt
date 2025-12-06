cmake_minimum_required(VERSION 3.0)

# 1. Name your project
project(PerfumeStore)

# 2. Find wxWidgets Package
# We need 'core' (GUI) and 'base' (Non-GUI utils)
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# 3. Add all your source files here
# If you add new .cpp files later, add them to this list!
set(SOURCES 
    main.cpp
    GUI_Base.cpp
)

# 4. Create the Executable
add_executable(MyShopApp ${SOURCES})

# 5. Link wxWidgets libraries to your app
target_link_libraries(MyShopApp ${wxWidgets_LIBRARIES})