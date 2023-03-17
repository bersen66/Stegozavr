all:
	git submodule update --init
	mkdir release -v -p && \
    	cd release && \
		conan install .. --build=missing && \
		cp ../configs/static_config.yaml config_dev.yaml && \
		cp ../configs/dynamic_config.json dynamic_config_fallback.json && \
		cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_TYPE=Release -DUSERVER_DOWNLOAD_PACKAGES=ON -DUSERVER_NO_WERROR=ON -DUSERVER_FEATURE_UNIVERSAL=ON -DUSERVER_FEATURE_MONGODB=OFF -DUSERVER_LTO=OFF -DUSERVER_FEATURE_CLICKHOUSE=OFF -DUSERVER_FEATURE_GRPC=OFF -DUSERVER_FEATURE_RABBITMQ=OFF -DUSERVER_FEATURE_REDIS=OFF -DUSERVER_FEATURE_POSTGRESQL=ON -DSTEGOZAVR_ENABLE_UNIT_TESTS=ON -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake .. && \
		cmake --build . -j 6 && \
		cd tests/unit && \
		cp -R ../../../tests/unit/resources .  &&\
        ./EngineTests && \
        echo 'BUILD SUCCESS'

run-tests:
	git submodule update --init && \
	mkdir release -v -p && \
		cd release && \
		conan install .. --build=missing && \
		cp ../configs/static_config.yaml config_dev.yaml && \
        cp ../configs/dynamic_config.json dynamic_config_fallback.json && \
		cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_TYPE=Release -DUSERVER_DOWNLOAD_PACKAGES=ON -DUSERVER_NO_WERROR=ON -DUSERVER_FEATURE_UNIVERSAL=ON -DUSERVER_FEATURE_MONGODB=OFF -DUSERVER_LTO=OFF -DUSERVER_FEATURE_CLICKHOUSE=OFF -DUSERVER_FEATURE_GRPC=OFF -DUSERVER_FEATURE_RABBITMQ=OFF -DUSERVER_FEATURE_REDIS=OFF -DUSERVER_FEATURE_POSTGRESQL=ON -DSTEGOZAVR_ENABLE_UNIT_TESTS=ON -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake .. && \
		cmake --build . -j 6 && \
		cd tests/unit && \
		cp -R ../../../tests/unit/resources .  &&\
		./EngineTests

build-release:
	git submodule update --init && \
	mkdir release -v -p && \
		cd release && \
		conan install .. --build=missing && \
		cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_TYPE=Release -DUSERVER_DOWNLOAD_PACKAGES=ON -DUSERVER_NO_WERROR=ON -DUSERVER_FEATURE_UNIVERSAL=ON -DUSERVER_FEATURE_MONGODB=OFF -DUSERVER_LTO=OFF -DUSERVER_FEATURE_CLICKHOUSE=OFF -DUSERVER_FEATURE_GRPC=OFF -DUSERVER_FEATURE_RABBITMQ=OFF -DUSERVER_FEATURE_REDIS=OFF -DUSERVER_FEATURE_POSTGRESQL=ON -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake .. && \
		cmake --build . -j 6 && \
    	cp ../configs/static_config.yaml config_dev.yaml && \
    	cp ../configs/dynamic_config.json dynamic_config_fallback.json

run-release:
	git submodule update --init && \
	mkdir release -v -p && \
		cd release && \
		cp ../configs/static_config.yaml config_dev.yaml && \
        cp ../configs/dynamic_config.json dynamic_config_fallback.json && \
		conan install .. --build=missing && \
		cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_TYPE=Release -DUSERVER_DOWNLOAD_PACKAGES=ON -DUSERVER_NO_WERROR=ON -DUSERVER_FEATURE_MONGODB=OFF -DUSERVER_LTO=OFF -DUSERVER_FEATURE_CLICKHOUSE=OFF -DUSERVER_FEATURE_GRPC=OFF -DUSERVER_FEATURE_RABBITMQ=OFF -DUSERVER_FEATURE_REDIS=OFF -DUSERVER_FEATURE_UNIVERSAL=ON -DUSERVER_FEATURE_POSTGRESQL=ON -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake .. && \
		cmake --build . -j 6 && \
		./Stegozavr


