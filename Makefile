.PHONY: clean All

All:
	@echo "----------Building project:[ Led_Matrix - Upload ]----------"
	@"$(MAKE)" -f  "Led_Matrix.mk"
clean:
	@echo "----------Cleaning project:[ Led_Matrix - Upload ]----------"
	@"$(MAKE)" -f  "Led_Matrix.mk" clean
