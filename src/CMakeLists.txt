set ( srcFiles	main.cpp
	            DataFetcher.cpp
				DataReader.cpp )

#The "CURL_STATICLIB" is a most if you're building a static version
add_definitions ( -DCURL_STATICLIB )

add_executable ( LoLCDB ${srcFiles} )

#"curl-config" application can be used to detect required libraries
target_link_libraries ( LoLCDB ${CURL_LIBRARIES} )
