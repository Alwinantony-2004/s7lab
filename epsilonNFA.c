                 for (int l = 0; l < c_count; l++) {
                        if (strcmp(closure[l], trans[k].to) == 0) {
                            exists = 1;
                            break;
                        }
                    }
                    // if not, add it
                    if (!exists) {
                        strcpy(closure[c_count++], trans[k].to);
                    }
                }
            }
        }

        // Print the E-closure of the state
        printf("E-closure(%s) = { ", states[i]);
        for (int j = 0; j < c_count; j++) {
            printf("%s ", closure[j]);
        }
        printf("}\n");
    }

    return 0;
}
