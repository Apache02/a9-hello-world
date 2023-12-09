DOCKER_IMAGE = bk7252-hw-builder

all: builder build

builder:
	@if [ "$(shell docker images -q $(DOCKER_IMAGE) 2> /dev/null)" = "" ]; then \
		docker build -t $(DOCKER_IMAGE) .; \
	else \
		echo "Builder image already exists"; \
	fi

build:
	docker run --rm -u $(shell id -u) -v $(shell pwd)/src:/app $(DOCKER_IMAGE) make

clean:
	docker run --rm -v $(shell pwd)/src:/app $(DOCKER_IMAGE) "rm -Rf ./build"
	docker rmi $(DOCKER_IMAGE)

