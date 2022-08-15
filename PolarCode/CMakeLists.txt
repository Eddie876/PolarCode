# CMakeList.txt: PolarCode 的 CMake 專案，在此包含來源及定義
# 專案專屬邏輯。
#
cmake_minimum_required (VERSION 3.8)

# 將來源新增到此專案的可執行檔。
add_executable (PolarCode "PolarCode.cpp" "PolarCode.h")

# TODO: 新增測試，並視需要安裝目標。
