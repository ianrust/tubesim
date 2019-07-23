size_t cross_gradient_len = 3600;
size_t cross_gradient_width = 12;
size_t cross_gradient_height = 100;
uint8_t cross_gradient[3600] = { 250 , 56 , 254 , 250 , 57 , 254 , 250 , 56 , 253 , 250 , 56 , 254 , 249 , 56 , 253 , 255 , 214 , 0 , 255 , 214 , 0 , 250 , 56 , 254 , 251 , 57 , 255 , 250 , 57 , 254 , 250 , 57 , 254 , 249 , 56 , 254 , 247 , 61 , 253 , 247 , 60 , 254 , 247 , 60 , 253 , 248 , 60 , 254 , 247 , 60 , 253 , 255 , 214 , 0 , 255 , 214 , 0 , 247 , 60 , 253 , 247 , 61 , 253 , 247 , 61 , 253 , 247 , 61 , 253 , 247 , 60 , 253 , 244 , 64 , 253 , 244 , 64 , 253 , 244 , 65 , 253 , 245 , 64 , 253 , 244 , 65 , 253 , 255 , 214 , 0 , 255 , 214 , 0 , 245 , 64 , 253 , 245 , 65 , 253 , 245 , 64 , 253 , 244 , 64 , 253 , 245 , 64 , 254 , 241 , 68 , 252 , 242 , 69 , 253 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 241 , 68 , 252 , 241 , 69 , 252 , 239 , 72 , 252 , 238 , 72 , 252 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 239 , 73 , 252 , 239 , 72 , 252 , 235 , 76 , 251 , 235 , 76 , 251 , 235 , 76 , 251 , 235 , 76 , 251 , 236 , 76 , 252 , 255 , 214 , 0 , 255 , 214 , 0 , 235 , 76 , 251 , 235 , 76 , 251 , 236 , 76 , 251 , 236 , 76 , 252 , 235 , 76 , 251 , 232 , 80 , 251 , 233 , 80 , 251 , 233 , 80 , 251 , 232 , 80 , 250 , 233 , 80 , 251 , 255 , 214 , 0 , 255 , 214 , 0 , 233 , 80 , 251 , 233 , 80 , 251 , 233 , 80 , 251 , 233 , 80 , 251 , 232 , 80 , 250 , 230 , 84 , 250 , 230 , 84 , 251 , 229 , 84 , 250 , 230 , 84 , 250 , 229 , 84 , 250 , 255 , 214 , 0 , 255 , 214 , 0 , 230 , 85 , 251 , 230 , 84 , 250 , 230 , 84 , 250 , 230 , 84 , 251 , 229 , 84 , 250 , 227 , 88 , 250 , 226 , 88 , 249 , 227 , 88 , 249 , 227 , 88 , 250 , 227 , 88 , 250 , 227 , 88 , 250 , 227 , 88 , 250 , 227 , 88 , 250 , 227 , 88 , 250 , 227 , 88 , 250 , 227 , 88 , 250 , 227 , 89 , 250 , 225 , 92 , 250 , 225 , 92 , 250 , 224 , 92 , 249 , 224 , 92 , 249 , 224 , 92 , 249 , 225 , 92 , 250 , 224 , 92 , 249 , 225 , 92 , 250 , 224 , 91 , 249 , 224 , 93 , 250 , 224 , 92 , 249 , 224 , 92 , 250 , 221 , 95 , 249 , 221 , 96 , 249 , 222 , 96 , 249 , 221 , 96 , 249 , 221 , 96 , 249 , 255 , 214 , 0 , 255 , 214 , 0 , 221 , 96 , 249 , 221 , 96 , 248 , 222 , 96 , 249 , 221 , 96 , 249 , 221 , 96 , 248 , 218 , 100 , 248 , 218 , 100 , 248 , 218 , 100 , 248 , 218 , 100 , 248 , 218 , 100 , 248 , 255 , 214 , 0 , 255 , 214 , 0 , 219 , 100 , 249 , 218 , 100 , 248 , 218 , 100 , 248 , 218 , 100 , 248 , 218 , 100 , 248 , 215 , 104 , 247 , 216 , 104 , 248 , 216 , 103 , 248 , 216 , 104 , 248 , 216 , 104 , 248 , 255 , 214 , 0 , 255 , 214 , 0 , 216 , 103 , 248 , 216 , 104 , 248 , 215 , 104 , 247 , 215 , 104 , 247 , 216 , 104 , 248 , 213 , 108 , 247 , 213 , 108 , 248 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 213 , 108 , 248 , 213 , 108 , 247 , 210 , 112 , 247 , 210 , 112 , 247 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 210 , 112 , 247 , 210 , 112 , 247 , 207 , 116 , 246 , 207 , 116 , 246 , 207 , 116 , 247 , 206 , 116 , 246 , 207 , 116 , 246 , 255 , 214 , 0 , 255 , 214 , 0 , 208 , 116 , 247 , 207 , 116 , 246 , 207 , 116 , 246 , 207 , 116 , 246 , 207 , 116 , 246 , 204 , 120 , 246 , 204 , 120 , 246 , 205 , 119 , 246 , 204 , 120 , 246 , 205 , 120 , 247 , 255 , 214 , 0 , 255 , 214 , 0 , 204 , 120 , 246 , 204 , 120 , 246 , 205 , 119 , 246 , 204 , 120 , 246 , 204 , 120 , 246 , 201 , 124 , 245 , 202 , 123 , 246 , 202 , 123 , 246 , 201 , 124 , 245 , 201 , 124 , 245 , 255 , 214 , 0 , 255 , 214 , 0 , 202 , 123 , 246 , 201 , 123 , 245 , 201 , 123 , 245 , 202 , 123 , 246 , 202 , 123 , 246 , 199 , 128 , 245 , 198 , 127 , 244 , 198 , 127 , 245 , 198 , 127 , 245 , 199 , 128 , 245 , 198 , 127 , 245 , 199 , 128 , 245 , 199 , 128 , 245 , 199 , 128 , 245 , 198 , 127 , 245 , 198 , 128 , 245 , 198 , 127 , 245 , 196 , 131 , 245 , 195 , 131 , 244 , 195 , 131 , 244 , 195 , 131 , 244 , 195 , 131 , 244 , 196 , 132 , 245 , 196 , 131 , 245 , 195 , 131 , 244 , 195 , 131 , 244 , 196 , 131 , 245 , 195 , 131 , 244 , 195 , 131 , 244 , 192 , 135 , 243 , 192 , 135 , 243 , 193 , 135 , 244 , 193 , 136 , 244 , 193 , 136 , 244 , 255 , 214 , 0 , 255 , 214 , 0 , 192 , 135 , 243 , 192 , 135 , 243 , 192 , 135 , 244 , 192 , 136 , 244 , 193 , 135 , 244 , 190 , 139 , 243 , 190 , 139 , 243 , 190 , 139 , 243 , 190 , 139 , 243 , 190 , 139 , 243 , 255 , 214 , 0 , 255 , 214 , 0 , 191 , 139 , 244 , 190 , 139 , 244 , 190 , 139 , 244 , 190 , 139 , 244 , 190 , 139 , 243 , 188 , 144 , 243 , 187 , 144 , 243 , 187 , 143 , 243 , 187 , 143 , 243 , 187 , 143 , 242 , 255 , 214 , 0 , 255 , 214 , 0 , 186 , 143 , 242 , 187 , 143 , 243 , 188 , 144 , 243 , 188 , 144 , 244 , 187 , 144 , 243 , 184 , 147 , 242 , 185 , 148 , 243 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 185 , 148 , 243 , 184 , 147 , 242 , 182 , 152 , 242 , 181 , 151 , 242 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 181 , 151 , 242 , 182 , 152 , 243 , 179 , 155 , 242 , 179 , 156 , 242 , 178 , 155 , 241 , 178 , 155 , 241 , 179 , 156 , 242 , 255 , 214 , 0 , 255 , 214 , 0 , 178 , 155 , 241 , 178 , 155 , 241 , 179 , 156 , 242 , 178 , 155 , 241 , 178 , 155 , 241 , 176 , 160 , 241 , 176 , 159 , 241 , 176 , 159 , 241 , 176 , 160 , 241 , 175 , 159 , 241 , 255 , 214 , 0 , 255 , 214 , 0 , 175 , 159 , 241 , 175 , 159 , 241 , 176 , 160 , 241 , 176 , 160 , 241 , 175 , 159 , 241 , 173 , 163 , 240 , 172 , 163 , 240 , 173 , 163 , 240 , 173 , 163 , 241 , 172 , 163 , 240 , 255 , 214 , 0 , 255 , 214 , 0 , 172 , 162 , 240 , 173 , 164 , 241 , 173 , 163 , 241 , 173 , 163 , 240 , 173 , 163 , 240 , 170 , 167 , 240 , 170 , 167 , 240 , 170 , 167 , 240 , 171 , 168 , 241 , 170 , 167 , 240 , 170 , 167 , 240 , 170 , 167 , 240 , 170 , 167 , 240 , 170 , 167 , 240 , 170 , 167 , 240 , 170 , 168 , 240 , 170 , 167 , 240 , 167 , 171 , 239 , 167 , 171 , 240 , 167 , 171 , 240 , 166 , 171 , 239 , 166 , 171 , 239 , 167 , 171 , 240 , 167 , 171 , 239 , 167 , 171 , 239 , 167 , 171 , 239 , 167 , 171 , 239 , 167 , 171 , 239 , 167 , 171 , 239 , 165 , 175 , 239 , 164 , 175 , 239 , 164 , 175 , 239 , 165 , 175 , 239 , 164 , 175 , 239 , 255 , 214 , 0 , 255 , 214 , 0 , 164 , 174 , 239 , 164 , 175 , 239 , 164 , 174 , 238 , 164 , 174 , 239 , 165 , 176 , 239 , 161 , 179 , 238 , 161 , 179 , 238 , 161 , 179 , 238 , 161 , 179 , 238 , 161 , 179 , 238 , 255 , 214 , 0 , 255 , 214 , 0 , 161 , 179 , 238 , 162 , 179 , 239 , 161 , 179 , 239 , 161 , 179 , 238 , 161 , 179 , 238 , 158 , 183 , 238 , 158 , 183 , 238 , 158 , 182 , 237 , 158 , 183 , 238 , 158 , 183 , 238 , 255 , 214 , 0 , 255 , 214 , 0 , 158 , 182 , 238 , 158 , 182 , 237 , 158 , 183 , 238 , 158 , 183 , 238 , 159 , 184 , 238 , 156 , 187 , 237 , 156 , 187 , 238 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 155 , 186 , 237 , 156 , 187 , 238 , 153 , 191 , 237 , 152 , 190 , 236 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 153 , 191 , 237 , 153 , 191 , 237 , 150 , 194 , 236 , 151 , 195 , 237 , 150 , 195 , 237 , 150 , 195 , 236 , 151 , 195 , 237 , 255 , 214 , 0 , 255 , 214 , 0 , 150 , 194 , 236 , 150 , 195 , 236 , 149 , 194 , 236 , 150 , 194 , 236 , 150 , 194 , 236 , 147 , 199 , 236 , 148 , 199 , 236 , 147 , 198 , 236 , 147 , 199 , 236 , 147 , 198 , 235 , 255 , 214 , 0 , 255 , 214 , 0 , 147 , 198 , 236 , 147 , 199 , 236 , 147 , 199 , 236 , 147 , 199 , 236 , 147 , 198 , 236 , 145 , 203 , 236 , 144 , 202 , 235 , 145 , 203 , 236 , 144 , 202 , 235 , 144 , 202 , 235 , 255 , 214 , 0 , 255 , 214 , 0 , 144 , 202 , 235 , 144 , 203 , 235 , 145 , 203 , 236 , 145 , 203 , 236 , 144 , 202 , 235 , 141 , 207 , 235 , 141 , 206 , 235 , 141 , 207 , 235 , 141 , 206 , 235 , 142 , 207 , 235 , 141 , 206 , 235 , 141 , 206 , 235 , 141 , 206 , 235 , 141 , 206 , 235 , 141 , 206 , 235 , 141 , 206 , 235 , 141 , 206 , 235 , 138 , 211 , 235 , 139 , 210 , 235 , 138 , 211 , 235 , 138 , 210 , 234 , 138 , 211 , 235 , 138 , 210 , 234 , 137 , 210 , 234 , 138 , 211 , 235 , 139 , 210 , 234 , 138 , 210 , 234 , 138 , 210 , 234 , 139 , 211 , 235 , 135 , 215 , 234 , 135 , 215 , 234 , 135 , 214 , 234 , 136 , 214 , 234 , 135 , 214 , 234 , 255 , 214 , 0 , 255 , 214 , 0 , 136 , 214 , 234 , 135 , 214 , 234 , 135 , 214 , 233 , 135 , 214 , 233 , 136 , 214 , 234 , 133 , 219 , 234 , 132 , 218 , 233 , 132 , 219 , 234 , 132 , 218 , 233 , 133 , 218 , 233 , 255 , 214 , 0 , 255 , 214 , 0 , 133 , 218 , 233 , 133 , 218 , 233 , 132 , 218 , 233 , 132 , 219 , 234 , 132 , 218 , 233 , 130 , 222 , 233 , 130 , 223 , 233 , 130 , 222 , 233 , 130 , 222 , 233 , 130 , 222 , 233 , 255 , 214 , 0 , 255 , 214 , 0 , 130 , 222 , 233 , 130 , 222 , 233 , 130 , 222 , 233 , 129 , 222 , 232 , 130 , 223 , 233 , 128 , 227 , 233 , 127 , 226 , 232 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 128 , 226 , 232 , 127 , 226 , 233 , 125 , 230 , 232 , 124 , 230 , 232 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 125 , 230 , 232 , 124 , 230 , 231 , 121 , 234 , 232 , 120 , 234 , 232 , 121 , 234 , 232 , 121 , 235 , 232 , 122 , 234 , 231 , 255 , 214 , 0 , 255 , 214 , 0 , 121 , 234 , 231 , 121 , 234 , 231 , 121 , 234 , 231 , 121 , 234 , 231 , 122 , 234 , 232 , 118 , 238 , 231 , 119 , 239 , 232 , 118 , 238 , 231 , 118 , 238 , 231 , 118 , 237 , 231 , 255 , 214 , 0 , 255 , 214 , 0 , 118 , 238 , 231 , 118 , 238 , 231 , 119 , 238 , 231 , 119 , 238 , 231 , 118 , 238 , 230 , 116 , 242 , 230 , 116 , 242 , 231 , 115 , 242 , 230 , 115 , 243 , 231 , 116 , 242 , 230 , 255 , 214 , 0 , 255 , 214 , 0 , 115 , 243 , 231 , 115 , 242 , 230 , 116 , 242 , 230 , 115 , 242 , 231 , 115 , 241 , 230 , 112 , 246 , 230 , 113 , 246 , 230 , 112 , 247 , 230 , 113 , 246 , 230 , 113 , 246 , 230 , 113 , 246 , 230 , 112 , 245 , 229 , 112 , 246 , 230 , 113 , 246 , 230 , 113 , 246 , 230 , 113 , 246 , 230 , 112 , 246 , 230 , 109 , 250 , 230 , 111 , 250 , 230 , 110 , 250 , 230 , 110 , 249 , 229 , 110 , 250 , 229 , 110 , 250 , 229 , 109 , 250 , 229 , 110 , 249 , 229 , 110 , 250 , 229 , 110 , 250 , 229 , 110 , 250 , 230 , 110 , 250 , 229 , 108 , 253 , 229 , 108 , 253 , 229 , 107 , 253 , 229 , 107 , 254 , 230 , 108 , 253 , 229 , 255 , 214 , 0 , 255 , 214 , 0 , 108 , 254 , 230 , 108 , 253 , 229 , 108 , 253 , 229 , 108 , 253 , 229 , 108 , 253 , 229 , 110 , 251 , 230 , 110 , 251 , 230 , 109 , 250 , 229 , 110 , 250 , 229 , 110 , 251 , 230 , 255 , 214 , 0 , 255 , 214 , 0 , 110 , 250 , 229 , 110 , 250 , 229 , 110 , 250 , 230 , 110 , 251 , 230 , 110 , 251 , 230 , 113 , 246 , 230 , 113 , 246 , 230 , 113 , 246 , 229 , 113 , 246 , 229 , 113 , 246 , 229 , 255 , 214 , 0 , 255 , 214 , 0 , 112 , 247 , 230 , 113 , 247 , 231 , 113 , 246 , 230 , 113 , 246 , 230 , 113 , 246 , 230 , 115 , 243 , 231 , 116 , 242 , 230 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 116 , 242 , 230 , 115 , 242 , 230 , 118 , 238 , 231 , 118 , 238 , 231 , 254 , 214 , 1 , 254 , 214 , 1 , 254 , 214 , 1 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 118 , 239 , 232 , 118 , 239 , 231 , 121 , 234 , 231 , 121 , 233 , 231 , 121 , 234 , 231 , 121 , 234 , 231 , 122 , 234 , 232 , 255 , 214 , 0 , 255 , 214 , 0 , 121 , 235 , 232 , 121 , 234 , 231 , 122 , 234 , 231 , 121 , 234 , 231 , 121 , 234 , 232 , 124 , 230 , 232 , 124 , 230 , 232 , 124 , 230 , 232 , 125 , 230 , 232 , 124 , 230 , 232 , 255 , 214 , 0 , 255 , 214 , 0 , 124 , 230 , 232 , 124 , 231 , 233 , 124 , 230 , 232 , 124 , 230 , 232 , 124 , 230 , 232 , 128 , 226 , 233 , 127 , 226 , 232 , 128 , 226 , 233 , 127 , 226 , 232 , 127 , 226 , 233 , 255 , 214 , 1 , 255 , 214 , 0 , 128 , 226 , 233 , 127 , 226 , 232 , 127 , 226 , 232 , 127 , 226 , 233 , 128 , 226 , 233 , 130 , 222 , 233 , 130 , 222 , 233 , 130 , 222 , 233 , 129 , 222 , 233 , 129 , 222 , 233 , 130 , 222 , 233 , 130 , 222 , 233 , 130 , 223 , 234 , 130 , 222 , 232 , 130 , 222 , 233 , 129 , 223 , 233 , 130 , 222 , 233 , 133 , 218 , 233 , 133 , 217 , 233 , 133 , 218 , 233 , 133 , 218 , 233 , 133 , 217 , 233 , 132 , 218 , 232 , 132 , 217 , 233 , 132 , 218 , 234 , 133 , 218 , 233 , 132 , 218 , 234 , 133 , 218 , 233 , 133 , 217 , 233 , 136 , 213 , 234 , 135 , 214 , 234 , 135 , 213 , 233 , 136 , 214 , 234 , 136 , 214 , 234 , 255 , 214 , 0 , 255 , 214 , 0 , 136 , 214 , 234 , 136 , 214 , 234 , 135 , 214 , 234 , 135 , 213 , 234 , 135 , 214 , 234 , 138 , 210 , 235 , 139 , 210 , 234 , 138 , 210 , 234 , 139 , 210 , 234 , 139 , 210 , 234 , 255 , 214 , 0 , 255 , 214 , 0 , 139 , 210 , 235 , 138 , 209 , 234 , 138 , 210 , 235 , 139 , 210 , 234 , 138 , 209 , 234 , 142 , 206 , 236 , 141 , 207 , 236 , 141 , 205 , 234 , 142 , 206 , 234 , 142 , 206 , 234 , 255 , 214 , 0 , 255 , 214 , 0 , 142 , 206 , 235 , 141 , 206 , 236 , 141 , 206 , 235 , 141 , 205 , 235 , 142 , 206 , 235 , 145 , 202 , 236 , 145 , 202 , 236 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 145 , 202 , 236 , 145 , 202 , 236 , 147 , 197 , 236 , 148 , 198 , 237 , 255 , 214 , 1 , 255 , 214 , 1 , 255 , 214 , 1 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 148 , 198 , 236 , 148 , 198 , 236 , 150 , 193 , 236 , 150 , 193 , 236 , 150 , 194 , 236 , 150 , 193 , 236 , 151 , 194 , 237 , 255 , 214 , 0 , 255 , 214 , 0 , 150 , 193 , 236 , 151 , 194 , 237 , 150 , 193 , 236 , 150 , 193 , 236 , 150 , 193 , 236 , 154 , 190 , 237 , 153 , 190 , 237 , 153 , 189 , 237 , 153 , 190 , 237 , 153 , 189 , 237 , 255 , 214 , 0 , 255 , 214 , 0 , 153 , 189 , 237 , 153 , 189 , 237 , 153 , 189 , 237 , 153 , 189 , 237 , 153 , 189 , 236 , 156 , 185 , 237 , 156 , 186 , 237 , 156 , 186 , 237 , 156 , 185 , 237 , 156 , 186 , 237 , 255 , 214 , 1 , 255 , 214 , 0 , 156 , 185 , 237 , 156 , 185 , 237 , 156 , 186 , 237 , 156 , 185 , 237 , 156 , 185 , 237 , 159 , 181 , 238 , 159 , 181 , 238 , 159 , 181 , 238 , 159 , 181 , 238 , 159 , 181 , 238 , 159 , 181 , 238 , 160 , 182 , 239 , 159 , 181 , 238 , 159 , 182 , 238 , 160 , 182 , 238 , 159 , 181 , 238 , 159 , 181 , 238 , 161 , 177 , 238 , 162 , 177 , 238 , 162 , 177 , 238 , 162 , 177 , 238 , 162 , 177 , 239 , 162 , 177 , 237 , 162 , 178 , 238 , 162 , 178 , 239 , 162 , 177 , 238 , 162 , 178 , 238 , 162 , 177 , 238 , 162 , 177 , 238 , 165 , 173 , 239 , 164 , 173 , 238 , 164 , 173 , 238 , 165 , 173 , 239 , 165 , 174 , 239 , 255 , 214 , 0 , 255 , 214 , 0 , 165 , 173 , 239 , 165 , 174 , 240 , 165 , 174 , 239 , 165 , 173 , 239 , 165 , 174 , 239 , 168 , 169 , 239 , 168 , 169 , 239 , 167 , 169 , 239 , 167 , 169 , 239 , 168 , 169 , 239 , 255 , 214 , 0 , 255 , 214 , 0 , 167 , 169 , 239 , 167 , 169 , 239 , 168 , 170 , 240 , 168 , 169 , 239 , 168 , 169 , 239 , 170 , 165 , 239 , 171 , 166 , 240 , 171 , 166 , 239 , 171 , 165 , 239 , 170 , 165 , 238 , 255 , 214 , 0 , 255 , 214 , 0 , 171 , 165 , 240 , 170 , 165 , 239 , 171 , 166 , 240 , 170 , 165 , 240 , 171 , 166 , 240 , 173 , 161 , 240 , 173 , 161 , 240 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 174 , 161 , 240 , 174 , 162 , 241 , 177 , 158 , 241 , 176 , 157 , 241 , 255 , 214 , 1 , 255 , 214 , 1 , 255 , 214 , 1 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 177 , 158 , 241 , 177 , 158 , 241 , 179 , 153 , 241 , 180 , 153 , 242 , 179 , 153 , 241 , 179 , 153 , 241 , 179 , 153 , 241 , 255 , 214 , 0 , 255 , 214 , 0 , 179 , 153 , 241 , 180 , 154 , 242 , 179 , 153 , 241 , 180 , 153 , 241 , 179 , 153 , 241 , 182 , 149 , 241 , 182 , 149 , 242 , 182 , 149 , 242 , 182 , 149 , 242 , 182 , 149 , 242 , 255 , 214 , 0 , 255 , 214 , 0 , 182 , 148 , 241 , 183 , 150 , 242 , 182 , 149 , 242 , 182 , 149 , 242 , 183 , 150 , 242 , 185 , 145 , 242 , 185 , 145 , 242 , 185 , 145 , 242 , 185 , 145 , 243 , 185 , 145 , 242 , 255 , 214 , 1 , 255 , 214 , 0 , 185 , 145 , 242 , 185 , 145 , 243 , 185 , 145 , 243 , 185 , 145 , 242 , 185 , 145 , 243 , 189 , 140 , 243 , 188 , 141 , 242 , 189 , 141 , 243 , 187 , 141 , 242 , 188 , 141 , 243 , 188 , 141 , 243 , 188 , 140 , 243 , 188 , 141 , 243 , 187 , 140 , 242 , 188 , 141 , 243 , 189 , 140 , 243 , 187 , 141 , 242 , 191 , 137 , 243 , 191 , 136 , 243 , 191 , 137 , 243 , 191 , 136 , 243 , 190 , 137 , 243 , 191 , 137 , 242 , 191 , 137 , 243 , 191 , 136 , 244 , 191 , 137 , 244 , 191 , 137 , 243 , 191 , 137 , 243 , 191 , 137 , 243 , 193 , 133 , 244 , 194 , 133 , 244 , 193 , 133 , 243 , 194 , 133 , 244 , 194 , 132 , 244 , 255 , 214 , 0 , 255 , 214 , 0 , 194 , 133 , 244 , 194 , 133 , 244 , 193 , 133 , 244 , 194 , 133 , 244 , 194 , 133 , 244 , 196 , 128 , 244 , 196 , 128 , 244 , 196 , 129 , 244 , 197 , 129 , 244 , 197 , 129 , 244 , 255 , 214 , 0 , 255 , 214 , 0 , 197 , 129 , 245 , 197 , 129 , 245 , 196 , 129 , 244 , 197 , 129 , 244 , 197 , 128 , 244 , 199 , 125 , 245 , 199 , 125 , 244 , 199 , 125 , 244 , 200 , 125 , 244 , 199 , 125 , 244 , 255 , 214 , 0 , 255 , 214 , 0 , 200 , 125 , 245 , 199 , 124 , 244 , 199 , 125 , 244 , 200 , 125 , 245 , 199 , 124 , 244 , 202 , 120 , 244 , 203 , 120 , 246 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 202 , 121 , 245 , 202 , 120 , 245 , 205 , 116 , 245 , 205 , 116 , 246 , 255 , 214 , 1 , 255 , 214 , 1 , 255 , 214 , 1 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 205 , 116 , 246 , 206 , 116 , 246 , 209 , 112 , 246 , 208 , 113 , 246 , 208 , 112 , 246 , 209 , 113 , 247 , 208 , 112 , 246 , 255 , 214 , 0 , 255 , 214 , 0 , 208 , 112 , 246 , 208 , 112 , 246 , 208 , 113 , 247 , 208 , 112 , 246 , 208 , 113 , 246 , 211 , 109 , 246 , 211 , 109 , 247 , 211 , 109 , 246 , 211 , 109 , 246 , 211 , 109 , 247 , 255 , 214 , 0 , 255 , 214 , 0 , 211 , 109 , 247 , 211 , 109 , 247 , 211 , 108 , 246 , 211 , 108 , 246 , 211 , 109 , 247 , 214 , 105 , 247 , 214 , 104 , 248 , 215 , 104 , 248 , 214 , 105 , 247 , 215 , 105 , 248 , 255 , 214 , 1 , 255 , 214 , 0 , 214 , 104 , 247 , 214 , 104 , 247 , 215 , 104 , 248 , 214 , 105 , 247 , 215 , 105 , 248 , 217 , 101 , 247 , 218 , 100 , 248 , 218 , 100 , 248 , 216 , 100 , 247 , 217 , 100 , 247 , 217 , 100 , 248 , 217 , 100 , 247 , 217 , 101 , 248 , 217 , 101 , 248 , 217 , 100 , 247 , 217 , 100 , 247 , 217 , 101 , 248 , 220 , 96 , 248 , 219 , 96 , 248 , 220 , 97 , 248 , 220 , 96 , 248 , 220 , 96 , 248 , 220 , 97 , 248 , 220 , 96 , 248 , 219 , 96 , 248 , 220 , 97 , 248 , 220 , 96 , 248 , 220 , 97 , 248 , 220 , 96 , 248 , 223 , 93 , 249 , 223 , 92 , 248 , 222 , 92 , 248 , 223 , 93 , 249 , 223 , 92 , 249 , 255 , 214 , 0 , 255 , 214 , 0 , 222 , 92 , 248 , 223 , 93 , 249 , 222 , 92 , 248 , 223 , 92 , 248 , 223 , 93 , 249 , 225 , 88 , 249 , 226 , 88 , 249 , 225 , 88 , 249 , 226 , 88 , 249 , 226 , 88 , 250 , 255 , 214 , 0 , 255 , 214 , 0 , 225 , 88 , 249 , 226 , 88 , 250 , 225 , 88 , 249 , 226 , 88 , 249 , 225 , 88 , 249 , 229 , 84 , 250 , 228 , 84 , 249 , 229 , 85 , 249 , 228 , 84 , 248 , 229 , 85 , 249 , 255 , 214 , 0 , 255 , 214 , 0 , 228 , 84 , 249 , 228 , 84 , 249 , 228 , 84 , 250 , 229 , 85 , 250 , 228 , 84 , 249 , 232 , 80 , 250 , 231 , 80 , 250 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 232 , 81 , 250 , 231 , 80 , 249 , 234 , 76 , 250 , 234 , 76 , 251 , 255 , 213 , 1 , 255 , 213 , 1 , 255 , 213 , 1 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 255 , 214 , 0 , 235 , 76 , 251 , 234 , 76 , 250 , 237 , 72 , 251 , 238 , 72 , 252 , 237 , 72 , 251 , 237 , 72 , 251 , 237 , 72 , 251 , 255 , 214 , 0 , 255 , 214 , 0 , 237 , 72 , 251 , 237 , 72 , 251 , 237 , 72 , 251 , 237 , 72 , 250 , 236 , 72 , 250 , 240 , 68 , 251 , 240 , 68 , 251 , 240 , 68 , 251 , 240 , 68 , 251 , 240 , 68 , 252 , 255 , 214 , 0 , 255 , 214 , 0 , 240 , 68 , 251 , 240 , 68 , 251 , 240 , 68 , 252 , 239 , 68 , 251 , 240 , 68 , 252 , 243 , 64 , 252 , 244 , 65 , 253 , 242 , 64 , 251 , 243 , 64 , 252 , 243 , 64 , 252 , 255 , 213 , 1 , 255 , 214 , 0 , 243 , 64 , 252 , 243 , 64 , 252 , 243 , 64 , 252 , 243 , 64 , 252 , 243 , 64 , 252 , 246 , 60 , 252 , 247 , 60 , 253 , 245 , 60 , 252 , 247 , 60 , 253 , 246 , 60 , 252 , 247 , 60 , 253 , 245 , 60 , 252 , 246 , 60 , 253 , 246 , 60 , 253 , 245 , 60 , 252 , 246 , 60 , 252 , 246 , 60 , 253 , 249 , 55 , 253 , 249 , 56 , 253 , 249 , 56 , 253 , 249 , 56 , 253 , 248 , 56 , 253 , 248 , 56 , 253 , 249 , 56 , 253 , 249 , 55 , 253 , 249 , 56 , 253 , 249 , 56 , 254 , 249 , 56 , 253 , 249 , 56 , 253 };
