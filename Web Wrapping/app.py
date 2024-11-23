import streamlit as st

import subprocess

def run_exe(input_expression):
    # Run the .exe file with input
    result = subprocess.run(
        ["main.exe"],  # Replace with the actual path to the exe
        input=input_expression,        # Input string for the exe
        text=True,                     # Send input as a text string
        capture_output=False            # Capture the output from the exe
    )
    return 0  # Return the exe's output

class RegEx:
    def __init__(self, infix):
        self.infix = infix

    def check_regular_expression(self):
        parentheses_stack = []

        # Variable to keep track of the last character for invalid sequences
        last_char = None

        for i, c in enumerate(self.infix):
            # Check for valid characters
            if not (c.isalnum() or c in "+*()"):
                raise ValueError(f"Invalid character in the regular expression: '{c}'")

            # Check for invalid sequences
            if c == '+':
                if i == 0 or i == len(self.infix) - 1:
                    raise ValueError(
                        "Operator '+' cannot be at the start or end of the regular expression"
                    )
                if last_char == '+':
                    raise ValueError(f"Invalid sequence: '{last_char}{c}'")

            if c == '*':
                if i == 0:
                    raise ValueError(
                        "Operator '*' cannot be at the start of the regular expression"
                    )
                if last_char in "*+":
                    raise ValueError(f"Invalid sequence: '{last_char}{c}'")

            # Parenthesis checking
            if c == '(':
                parentheses_stack.append(c)
            elif c == ')':
                if not parentheses_stack or parentheses_stack[-1] != '(':
                    raise ValueError("Unmatched parenthesis")
                parentheses_stack.pop()

                # Check for empty parentheses pair
                if i > 0 and self.infix[i - 1] == '(':
                    raise ValueError("Empty parentheses pair found")

            # Update last character
            last_char = c

        # Ensure all opened parentheses are closed
        if parentheses_stack:
            raise ValueError("Unmatched parenthesis")


st.title("RegEx2DFA")

# User input
user_expression = st.text_input("Enter your expression:")

try:
    regex = RegEx(user_expression)
    regex.check_regular_expression()
    # st.write("Regular expression is valid.")
except ValueError as e:
    st.write(f"Error: {e}")
    
run_exe(user_expression)
# st.write("Processing complete!")  
col1, col2= st.columns([1, 1])
with col1:
    if st.button("DFA") and user_expression:
        # Display the output image
        st.image("dfa.png", caption="DFA")

with col2:
    if st.button("NFA") and user_expression:
        # Display the output image
        st.image("nfa.png", caption="NFA")

if st.button("Both"):
    col4, col5 = st.columns([1, 1])
    with col4:
        # Display the output image
        
        st.image("nfa.png", caption="NFA")  
    with col5:    
        # Display the output image
        st.image("dfa.png", caption="DFA")   
