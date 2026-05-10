include("D:/qt-documents/server_part/build/Desktop_Qt_6_11_0_MinGW_64_bit-RelWithDebInfo/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/server_part-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "D:/qt-documents/server_part/build/Desktop_Qt_6_11_0_MinGW_64_bit-RelWithDebInfo/server_part.exe"
    GENERATE_QT_CONF
)
