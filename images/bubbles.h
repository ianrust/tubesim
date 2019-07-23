size_t bubbles_len = 1800;
size_t bubbles_width = 12;
size_t bubbles_height = 50;
uint8_t bubbles[1800] = { 201 , 110 , 151 , 209 , 114 , 156 , 208 , 107 , 153 , 208 , 113 , 157 , 194 , 122 , 160 , 182 , 125 , 160 , 181 , 136 , 167 , 176 , 131 , 164 , 183 , 127 , 164 , 186 , 121 , 161 , 194 , 119 , 160 , 187 , 109 , 151 , 237 , 146 , 187 , 233 , 145 , 187 , 214 , 132 , 172 , 210 , 144 , 180 , 204 , 164 , 191 , 186 , 160 , 185 , 185 , 163 , 188 , 193 , 163 , 191 , 203 , 153 , 188 , 217 , 151 , 191 , 233 , 150 , 194 , 226 , 137 , 183 , 199 , 106 , 150 , 190 , 112 , 152 , 178 , 133 , 162 , 185 , 173 , 193 , 175 , 202 , 209 , 168 , 205 , 211 , 180 , 204 , 214 , 190 , 188 , 209 , 218 , 178 , 212 , 239 , 166 , 211 , 242 , 144 , 195 , 218 , 108 , 163 , 196 , 130 , 166 , 194 , 149 , 180 , 181 , 177 , 194 , 169 , 202 , 209 , 147 , 213 , 209 , 139 , 212 , 205 , 146 , 200 , 202 , 148 , 175 , 186 , 152 , 144 , 167 , 153 , 107 , 143 , 172 , 89 , 135 , 194 , 91 , 144 , 163 , 159 , 176 , 182 , 189 , 205 , 167 , 204 , 210 , 152 , 212 , 210 , 149 , 230 , 221 , 146 , 229 , 221 , 151 , 215 , 214 , 160 , 211 , 214 , 162 , 205 , 211 , 171 , 184 , 200 , 191 , 155 , 185 , 186 , 124 , 163 , 178 , 181 , 198 , 181 , 197 , 210 , 162 , 206 , 209 , 144 , 209 , 205 , 137 , 214 , 208 , 135 , 212 , 206 , 138 , 207 , 204 , 146 , 210 , 209 , 151 , 217 , 215 , 160 , 203 , 209 , 186 , 177 , 198 , 181 , 146 , 176 , 199 , 158 , 190 , 183 , 161 , 186 , 168 , 186 , 198 , 157 , 198 , 202 , 141 , 190 , 194 , 139 , 197 , 198 , 146 , 212 , 210 , 145 , 214 , 211 , 151 , 213 , 210 , 155 , 194 , 199 , 175 , 174 , 190 , 176 , 154 , 177 , 171 , 111 , 149 , 173 , 129 , 162 , 176 , 171 , 191 , 179 , 193 , 206 , 175 , 189 , 202 , 169 , 191 , 204 , 163 , 200 , 206 , 162 , 199 , 205 , 169 , 193 , 203 , 185 , 184 , 200 , 205 , 171 , 198 , 200 , 149 , 182 , 195 , 141 , 175 , 187 , 144 , 174 , 180 , 156 , 180 , 191 , 172 , 194 , 208 , 178 , 204 , 212 , 179 , 208 , 208 , 186 , 209 , 215 , 187 , 212 , 222 , 175 , 207 , 231 , 159 , 197 , 238 , 132 , 181 , 221 , 101 , 155 , 204 , 153 , 186 , 217 , 168 , 200 , 213 , 170 , 200 , 200 , 151 , 183 , 190 , 124 , 162 , 179 , 104 , 145 , 178 , 106 , 146 , 194 , 119 , 160 , 195 , 114 , 155 , 157 , 58 , 105 , 206 , 73 , 131 , 235 , 88 , 151 , 155 , 102 , 133 , 168 , 111 , 144 , 175 , 114 , 148 , 191 , 116 , 155 , 212 , 119 , 164 , 213 , 107 , 156 , 211 , 99 , 150 , 216 , 112 , 161 , 212 , 136 , 174 , 218 , 136 , 176 , 239 , 121 , 173 , 227 , 92 , 150 , 234 , 162 , 200 , 232 , 162 , 199 , 218 , 151 , 187 , 212 , 140 , 178 , 215 , 133 , 174 , 207 , 114 , 159 , 197 , 98 , 145 , 190 , 103 , 146 , 199 , 149 , 178 , 201 , 151 , 180 , 207 , 121 , 162 , 203 , 97 , 145 , 250 , 144 , 193 , 248 , 157 , 201 , 229 , 168 , 202 , 208 , 165 , 193 , 196 , 160 , 186 , 194 , 160 , 185 , 198 , 162 , 188 , 195 , 170 , 192 , 186 , 184 , 198 , 175 , 168 , 184 , 185 , 149 , 175 , 173 , 113 , 147 , 200 , 83 , 136 , 195 , 91 , 140 , 189 , 113 , 152 , 191 , 136 , 168 , 189 , 151 , 177 , 184 , 160 , 182 , 183 , 170 , 188 , 178 , 182 , 194 , 168 , 193 , 198 , 174 , 199 , 204 , 192 , 198 , 210 , 196 , 184 , 204 , 199 , 95 , 146 , 204 , 97 , 149 , 211 , 98 , 152 , 214 , 107 , 159 , 210 , 123 , 168 , 199 , 137 , 174 , 189 , 161 , 186 , 184 , 187 , 202 , 168 , 203 , 207 , 168 , 214 , 214 , 170 , 211 , 213 , 171 , 208 , 214 , 228 , 130 , 179 , 252 , 144 , 196 , 252 , 123 , 182 , 225 , 94 , 154 , 209 , 99 , 152 , 203 , 122 , 165 , 182 , 148 , 175 , 165 , 168 , 183 , 150 , 189 , 192 , 144 , 200 , 197 , 145 , 205 , 203 , 134 , 194 , 192 , 234 , 107 , 163 , 245 , 110 , 169 , 255 , 105 , 169 , 243 , 87 , 153 , 235 , 88 , 150 , 233 , 92 , 152 , 216 , 81 , 139 , 207 , 83 , 137 , 203 , 91 , 141 , 203 , 83 , 136 , 224 , 77 , 139 , 234 , 76 , 142 , 206 , 96 , 147 , 214 , 97 , 150 , 221 , 90 , 148 , 232 , 91 , 152 , 247 , 100 , 162 , 238 , 94 , 155 , 228 , 98 , 154 , 248 , 130 , 182 , 250 , 147 , 194 , 247 , 135 , 185 , 248 , 107 , 167 , 240 , 88 , 152 , 187 , 112 , 151 , 187 , 106 , 147 , 191 , 100 , 144 , 212 , 100 , 151 , 234 , 90 , 152 , 233 , 86 , 149 , 234 , 107 , 163 , 237 , 131 , 180 , 231 , 144 , 187 , 240 , 147 , 192 , 249 , 122 , 178 , 234 , 94 , 155 , 226 , 154 , 192 , 232 , 157 , 196 , 231 , 153 , 193 , 237 , 138 , 185 , 240 , 100 , 161 , 231 , 84 , 147 , 224 , 99 , 155 , 207 , 99 , 149 , 190 , 94 , 140 , 204 , 102 , 150 , 224 , 97 , 153 , 229 , 88 , 149 , 211 , 107 , 156 , 230 , 128 , 176 , 226 , 133 , 178 , 235 , 129 , 178 , 240 , 107 , 165 , 225 , 84 , 145 , 227 , 100 , 156 , 233 , 110 , 165 , 226 , 99 , 155 , 225 , 92 , 150 , 233 , 87 , 150 , 242 , 87 , 153 , 218 , 129 , 173 , 217 , 135 , 176 , 198 , 128 , 165 , 194 , 122 , 160 , 199 , 106 , 151 , 196 , 99 , 145 , 206 , 121 , 163 , 216 , 129 , 172 , 211 , 107 , 156 , 211 , 92 , 146 , 222 , 89 , 147 , 237 , 93 , 155 , 211 , 183 , 206 , 202 , 183 , 203 , 183 , 179 , 194 , 176 , 174 , 188 , 177 , 162 , 181 , 184 , 171 , 189 , 190 , 193 , 208 , 190 , 189 , 205 , 202 , 176 , 201 , 202 , 146 , 181 , 202 , 113 , 157 , 204 , 96 , 146 , 164 , 140 , 162 , 175 , 166 , 183 , 167 , 187 , 194 , 166 , 200 , 202 , 173 , 204 , 207 , 166 , 197 , 200 , 166 , 195 , 201 , 180 , 197 , 207 , 192 , 183 , 202 , 216 , 177 , 206 , 227 , 157 , 194 , 225 , 136 , 180 , 200 , 119 , 160 , 197 , 144 , 175 , 177 , 183 , 195 , 165 , 205 , 205 , 159 , 209 , 208 , 164 , 199 , 203 , 179 , 172 , 190 , 185 , 149 , 177 , 199 , 148 , 181 , 211 , 145 , 183 , 221 , 140 , 183 , 222 , 135 , 180 , 227 , 110 , 163 , 210 , 128 , 169 , 170 , 155 , 174 , 159 , 178 , 185 , 172 , 190 , 200 , 187 , 183 , 200 , 198 , 149 , 181 , 192 , 114 , 156 , 210 , 117 , 164 , 212 , 110 , 160 , 209 , 105 , 156 , 208 , 101 , 153 , 220 , 91 , 148 , 226 , 127 , 174 , 201 , 158 , 186 , 185 , 155 , 179 , 176 , 110 , 148 , 158 , 71 , 116 , 173 , 75 , 126 , 204 , 91 , 147 , 223 , 89 , 152 , 231 , 86 , 153 , 233 , 89 , 153 , 235 , 93 , 157 , 194 , 92 , 140 , 209 , 128 , 169 , 193 , 157 , 183 , 199 , 169 , 193 , 228 , 162 , 200 , 231 , 153 , 195 , 219 , 153 , 193 , 213 , 140 , 183 , 203 , 109 , 159 , 214 , 99 , 156 , 225 , 89 , 151 , 232 , 86 , 151 , 188 , 153 , 177 , 198 , 175 , 195 , 183 , 187 , 199 , 174 , 191 , 199 , 177 , 194 , 204 , 174 , 198 , 206 , 166 , 210 , 213 , 165 , 209 , 212 , 183 , 210 , 219 , 196 , 182 , 205 , 210 , 133 , 175 , 213 , 99 , 153 , 195 , 152 , 179 , 181 , 156 , 177 , 165 , 175 , 185 , 163 , 198 , 200 , 156 , 210 , 208 , 147 , 213 , 209 , 146 , 219 , 212 , 156 , 227 , 221 , 156 , 216 , 214 , 177 , 199 , 210 , 203 , 156 , 188 , 209 , 122 , 167 , 213 , 93 , 146 , 201 , 116 , 157 , 182 , 167 , 186 , 163 , 192 , 196 , 150 , 198 , 198 , 154 , 202 , 204 , 166 , 188 , 199 , 172 , 181 , 198 , 169 , 176 , 194 , 190 , 178 , 202 , 207 , 162 , 195 , 211 , 147 , 184 , 241 , 83 , 149 , 218 , 102 , 153 , 192 , 164 , 187 , 171 , 195 , 203 , 156 , 202 , 202 , 158 , 195 , 201 , 160 , 157 , 178 , 158 , 135 , 163 , 172 , 152 , 179 , 176 , 147 , 177 , 176 , 131 , 164 , 177 , 123 , 159 , 235 , 88 , 151 , 225 , 100 , 156 , 212 , 136 , 175 , 207 , 169 , 195 , 193 , 186 , 202 , 174 , 170 , 185 , 171 , 143 , 168 , 185 , 151 , 178 , 171 , 149 , 170 , 177 , 153 , 175 , 194 , 151 , 179 , 186 , 131 , 163 , 237 , 87 , 151 , 229 , 100 , 157 , 214 , 129 , 171 , 193 , 148 , 177 , 176 , 172 , 187 , 181 , 189 , 200 , 186 , 183 , 200 , 182 , 178 , 195 , 174 , 173 , 187 , 186 , 175 , 192 , 203 , 163 , 190 , 195 , 135 , 169 , 241 , 85 , 151 , 227 , 89 , 149 , 200 , 101 , 148 , 173 , 118 , 150 , 155 , 152 , 169 , 156 , 189 , 194 , 160 , 210 , 209 , 167 , 221 , 219 , 172 , 216 , 215 , 170 , 183 , 192 , 186 , 148 , 174 , 189 , 122 , 158 , 237 , 79 , 146 , 250 , 112 , 172 , 230 , 134 , 180 , 202 , 147 , 179 , 193 , 178 , 199 , 183 , 201 , 211 , 164 , 208 , 209 , 163 , 211 , 211 , 176 , 205 , 209 , 190 , 188 , 202 , 209 , 163 , 192 , 207 , 132 , 171 , 244 , 88 , 154 , 255 , 127 , 184 , 233 , 161 , 199 , 219 , 174 , 203 , 218 , 175 , 205 , 201 , 165 , 193 , 181 , 159 , 182 , 185 , 161 , 185 , 195 , 152 , 182 , 206 , 146 , 182 , 220 , 150 , 187 , 217 , 139 , 179 , 192 , 84 , 134 , 183 , 98 , 140 , 168 , 128 , 155 , 174 , 146 , 169 , 178 , 131 , 163 , 169 , 118 , 151 , 171 , 130 , 160 , 191 , 142 , 174 , 196 , 121 , 162 , 199 , 110 , 156 , 204 , 113 , 157 , 198 , 102 , 148 , 193 , 180 , 198 , 184 , 175 , 192 , 166 , 168 , 183 , 158 , 154 , 171 , 156 , 132 , 156 , 163 , 135 , 160 , 172 , 159 , 179 , 184 , 158 , 183 , 198 , 134 , 171 , 191 , 98 , 145 , 203 , 89 , 141 , 219 , 94 , 150 , 177 , 202 , 207 , 178 , 201 , 207 , 177 , 195 , 205 , 187 , 197 , 209 , 197 , 193 , 210 , 195 , 191 , 208 , 191 , 201 , 213 , 197 , 196 , 212 , 212 , 176 , 204 , 215 , 147 , 186 , 220 , 123 , 169 , 206 , 94 , 145 , 164 , 167 , 182 , 175 , 181 , 195 , 181 , 195 , 206 , 182 , 196 , 207 , 180 , 192 , 204 , 173 , 190 , 200 , 165 , 194 , 200 , 168 , 195 , 202 , 179 , 189 , 201 , 192 , 177 , 198 , 209 , 166 , 196 , 202 , 145 , 180 , 182 , 160 , 183 , 184 , 165 , 187 , 176 , 161 , 182 , 169 , 154 , 175 , 173 , 155 , 177 , 172 , 163 , 182 , 162 , 172 , 184 , 158 , 176 , 186 , 168 , 186 , 196 , 173 , 181 , 194 , 187 , 172 , 193 , 180 , 154 , 179 , 181 , 127 , 161 , 195 , 135 , 171 , 199 , 131 , 170 , 201 , 120 , 163 , 210 , 118 , 167 , 211 , 128 , 174 , 200 , 149 , 184 , 196 , 167 , 195 , 189 , 180 , 199 , 190 , 186 , 203 , 202 , 190 , 210 , 195 , 180 , 201 , 221 , 143 , 185 , 236 , 151 , 195 , 225 , 132 , 179 , 206 , 102 , 153 , 210 , 95 , 152 , 211 , 107 , 160 , 188 , 120 , 161 , 169 , 128 , 160 , 162 , 144 , 166 , 164 , 149 , 170 , 184 , 151 , 178 , 184 , 143 , 173 , 197 , 101 , 149 , 197 , 101 , 149 , 199 , 107 , 154 , 207 , 118 , 164 , 204 , 116 , 164 , 179 , 108 , 150 , 168 , 124 , 157 , 182 , 160 , 185 , 167 , 158 , 179 , 173 , 144 , 172 , 195 , 120 , 161 , 192 , 94 , 143 , 218 , 129 , 175 , 209 , 132 , 174 , 192 , 141 , 174 , 188 , 152 , 180 , 195 , 162 , 191 , 190 , 172 , 196 , 182 , 185 , 202 , 185 , 197 , 211 , 194 , 208 , 221 , 200 , 182 , 206 , 219 , 142 , 184 , 209 , 105 , 156 , 202 , 145 , 180 , 194 , 164 , 190 , 171 , 198 , 207 , 163 , 214 , 215 , 164 , 215 , 216 , 163 , 219 , 218 , 161 , 226 , 222 , 164 , 226 , 223 , 166 , 214 , 216 , 178 , 194 , 207 , 202 , 168 , 195 , 196 , 140 , 175 , 189 , 146 , 176 , 179 , 172 , 190 , 149 , 214 , 210 , 131 , 229 , 214 , 129 , 221 , 208 , 128 , 220 , 207 , 122 , 218 , 204 , 118 , 205 , 194 , 129 , 194 , 190 , 151 , 181 , 189 , 180 , 168 , 188 , 184 , 151 , 178 , 244 , 115 , 171 , 254 , 127 , 182 , 255 , 137 , 191 , 245 , 121 , 175 , 238 , 105 , 163 , 231 , 102 , 159 , 223 , 109 , 161 , 205 , 101 , 150 , 220 , 118 , 166 , 210 , 114 , 160 , 200 , 111 , 155 , 185 , 100 , 142 , 217 , 88 , 144 , 209 , 82 , 137 , 207 , 84 , 138 , 208 , 84 , 138 , 221 , 88 , 146 , 225 , 96 , 153 , 232 , 118 , 170 , 234 , 130 , 179 , 222 , 120 , 168 , 230 , 134 , 180 , 238 , 149 , 193 , 227 , 142 , 184 };
