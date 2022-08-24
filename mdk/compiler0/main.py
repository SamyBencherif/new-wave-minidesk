
def quickload(filename):
  with open(filename, "rt") as fileobj:
    contents = fileobj.read()
  return contents

source = quickload("../human-compiler/" + 
"drawingProgram/drawingProgram.mdk")
expected = quickload("../human-compiler/" + 
"drawingProgram/rimpl/source.c")

# (1) IDENTIFY PROGRAM SECTIONS

def indented(line):
  return line.startswith("\t") or line.startswith(" ")

sections = {"init":[]}
currentSection = "init"
for line in source.split("\n"):
  if not line.strip():
    continue
  if not indented(line):
    sections[line] = []
    currentSection = line
  else:
    sections[currentSection].append(line)

#print(sections)

# (2) FIND ARRAYS

def hasLiteral(line, literal):

  # if literal=".push"
  # should detect:
  #   arr.push(...)
  # should NOT detect
  #   print("I am a pencil .push er")
  # should NOT detect
  #   program.pushingData(...)

  # for now a simple implementation that works as long as 
  # the program has 0 literal collisions
  return literal in line

arrays = []
for line in source.split("\n"):
  if hasLiteral(line, ".push"):
    arr = line.split(".push")[0].strip()
    arrays.append(arr)

#print(arrays)

# (3) DETECT DATA STRUCTURES
# (this contains step 2)

datastructs = {}

for line in source.split("\n"):
  if hasLiteral(line, ".push"):
    arr = line.split(".push")[0].strip()
    data = line.split(".push")[1].strip()
    # consume ( )
    data = data[1:-1]
    # consume spaces
    data = data.strip()
    # consume { }
    data = data[1:-1]

    # a list of variable names
    # (type specification happens in variable names)
    ds = []
    for k in data.split(","):
      k = k.strip()
      if ":" in k:
        k = k.split(":")[0]
      ds.append(k.strip())
    datastructs[arr] = (ds)

# (4) WRITE DEFINITIONS TO CODE

code_datastructs = ""
for name, ds in datastructs.items():
  code_datastructs += f"struct {name} {{\n"

  for var in ds:
    code_datastructs += f"  int {var};\n"

  code_datastructs += f"}}"
  
code_arraydefs = ""
arrcap = 1000
for arr in datastructs.keys():
  code_arraydefs += f"struct {name} {name}[{arrcap}];\n"
  code_arraydefs += f"  int {name}_index = 0;\n"
  code_arraydefs += f"  int {name}_size = 0;\n"
  # size == index except for when array rolls over
  # then size == cap and index goes back thru the array

code_arraymgmt = ""
for arr in datastructs.keys():
  code_arraymgmt += f"if ({name}_index == {arrcap})\n"
  code_arraymgmt += f"      {name}_index = 0;"


# (5) CODE TRANSLATION ACTIVITIES

section_translated = {}

for k,v in sections.items():
  v_translated = []
  for line in v:
    line_translated = ""
    if hasLiteral(line, ".push"):
      arr = line.split(".push")[0].strip()
      data = line.split(".push")[1].strip()
      # consume ( )
      data = data[1:-1]
      # consume spaces
      data = data.strip()
      # consume { }
      data = data[1:-1]

      ds = []
      for k in data.split(","):
        k = k.strip()
        if ":" in k:
          k = k.split(":")[0]
        ds.append(k.strip())


  section_translated[k] = v_translated

""""
Code translation includes for loops and array push
and if statements
"""

outprogram = f"""
#include "raylib"

// structures
{code_datastructs}

int main()
{{
  int screenWidth = 256;
  int screenHeight = 256;

  InitWindow(screenWidth, screenHeight, "My Program");

  SetTargetFPS(17); // 60ms latency for GUI applications
  SetExitKey(0);

  // arrays
  {code_arraydefs}

  while (!WindowShouldClose())
  {{
    BeginDrawing();
    
    if (IsMouseButtonDown(0))
    {{
      // mousedown
      // ... code translation activity
    }}

    // array mgmt
    {code_arraymgmt}

    // loop
    // ... code translation activity

    EndDrawing();

  }}

  CloseWindow();
  return 0;
}}

"""
print(outprogram)
