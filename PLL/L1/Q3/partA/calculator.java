// import packages from java
import java.awt.Color;
import java.awt.event.*;
import java.awt.*;
import java.util.concurrent.TimeUnit;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.swing.JButton;
import javax.swing.Timer;
import java.util.Stack;

public class calculator extends javax.swing.JFrame {

    // Variables declaration for GUI
    JButton[] btn = new JButton[10]; //numeric buttons
    JButton[] op = new JButton[4]; //operator buttons
    JButton clear; // AC button
    private javax.swing.JTextField displayBox; // display box to show output
    // End of variables declaration

    // true means operator is to be highlighted. false means numeric has to be highlighted
    boolean isOperator; 
    // true means that the result is displayed. False means still waiting for user to select choices
    boolean complete;
    // Number of operands chosen
    int operandNum;
    // Numeric key that is currently being highlighted
    int numIndex;
    // Operator key that is currently being highlighted
    int opIndex;
    // String storing the text to be displayed on calculator screen
    String displayString;
    // Array of possible operator inputs
    char[] operator = {'+','-','*','/'};

    // Constructor for calculator class
    public calculator() {
        initComponents(); // initialise the gui for the calculator
        // Initialise the various variables of calculator class
        isOperator = false;
        complete = false;
        operandNum = 0;
        numIndex = 0;
        opIndex = 0;
        displayString = "";
    }

    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        // This handles all the warnings and errors that may arise in the GUI
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        
        // Create a object of class calculator
        calculator calc = new calculator();
        // Display the calculator on screen
        calc.setVisible(true);

        // Define a timer function that calls every 1.5s and changes the current highlight key
        Timer timer = new Timer(1500, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                // If the result is displayed
                if(calc.complete){ 
                    // Highlight the 'AC' button to clear the output and start new calculation
                    calc.selectButton(calc.clear);
                }
                // If operator is to be chosen
                else if(calc.isOperator){
                    // De-Highlight the currently highlighted operator
                    calc.deselectButton(calc.op[calc.opIndex]);
                    // Increase the operator index by 1
                    calc.opIndex = (calc.opIndex+1)%4;
                    // Highlight the operator next in line
                    calc.selectButton(calc.op[calc.opIndex]);
                }
                else{
                    // De-Highlight the currently highlighted numeric
                    calc.deselectButton(calc.btn[calc.numIndex]);
                    // Increase the numeric index by 1
                    calc.numIndex = (calc.numIndex+1)%10;
                    // Highlight the numeric next in line
                    calc.selectButton(calc.btn[calc.numIndex]);
                }
            }
        });
        // Set timer to repeat function call after every 1.5s
        timer.setRepeats(true);
        // start the timer
        timer.start();
    }

    // Function sets the background color of the button to white
    public void deselectButton(JButton btn){
        btn.setBackground(Color.WHITE);
    }

    // Function sets the background color of button to yellow
    public void selectButton(JButton btn){
        btn.setBackground(Color.YELLOW);
    }

    // Evaluates the user query and produces output
    // Uses Nashorm engine to evaluate the string query
    public void evaluate() throws ScriptException{
        // create a new instance of Nashorm engine
        ScriptEngineManager manager = new ScriptEngineManager(null);
        ScriptEngine engine = manager.getEngineByName("js");
        // uses 'eval' function to evaluate the output
        Object result = engine.eval(displayString);
        // Display the result to the user screen
        displayString = result.toString();
        displayBox.setText(displayString);
    }

    // Defines a key press event
    public KeyListener keyPress(){
        return new KeyListener() {
            // When key is pressed
            public void keyPressed(KeyEvent e){
                // If 'ENTER' is pressed and waiting for numeric operand from user
                if(e.getKeyCode()==KeyEvent.VK_ENTER && !isOperator && !complete){
                    // de-highlight the selected numeric key
                    deselectButton(btn[numIndex]);
                    // append the number to the display string
                    displayString += Integer.toString(numIndex);
                    // set numeric index to 0 for next time when the numeric
                    // keypad starts highlighting
                    numIndex = 0;
                    // The code now waits for operator
                    isOperator = true;
                    // Increase the number of operands by 1
                    operandNum += 1;
                }
                // if 'ENTER' is pressed and waiting for operator
                else if(e.getKeyCode()==KeyEvent.VK_ENTER && isOperator && !complete){
                    // de-highlight the current operator key
                    deselectButton(op[opIndex]);
                    // append the operator to display string
                    displayString += operator[opIndex];
                    // set operator index to 0 for next time when the operator keypad
                    // starts highlighting
                    opIndex = 0;
                    // The code now waits for numeric operand
                    isOperator = false;
                }
                // if 'ENTER' is pressed and 'AC' is highlighted i.e. result is displayed to screen
                else if(e.getKeyCode()==KeyEvent.VK_ENTER && complete){
                    // de-highlight the 'AC' button
                    deselectButton(clear);
                    // clear the display string
                    displayString = "";
                    // set number of operands to 0 for new calculation
                    operandNum = 0;
                    // set complete = false
                    complete = false;
                }
                // display the displayString on the screen
                displayBox.setText(displayString);
                // If 2 numeric operands are given
                if(operandNum==2){
                    // The code is ready to calculate the result
                    complete = true;
                    // The code will now wait for numeric input when calculation begins afresh
                    isOperator = false;
                    // Call the evaluate function to calculate final answer. The function
                    //  evaluates matchematical expression
                    try{evaluate();}
                    catch(ScriptException err){}
                }
            }
            // When key is released
            public void keyReleased(KeyEvent e) {
            }
            // When key is typed
            public void keyTyped(KeyEvent e) {
            }
        };
    }

        /**
     * This method is called from within the constructor to initialize the form.
     * The content of this method is always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // This is auto-generated code for GUI from Netbeans
    private void initComponents() {
        // Initialise the various components of the form
        displayBox = new javax.swing.JTextField();  // Textfield to display output
        //Buttons numeric
        btn[1] = new javax.swing.JButton();
        btn[2] = new javax.swing.JButton();
        btn[3] = new javax.swing.JButton();
        btn[4] = new javax.swing.JButton();
        btn[5] = new javax.swing.JButton();
        btn[6] = new javax.swing.JButton();
        btn[7] = new javax.swing.JButton();
        btn[8] = new javax.swing.JButton();
        btn[9] = new javax.swing.JButton();
        btn[0] = new javax.swing.JButton();
        // Buttons operator
        op[0] = new javax.swing.JButton();
        op[1] = new javax.swing.JButton();
        op[2] = new javax.swing.JButton();
        op[3] = new javax.swing.JButton();
        // AC Button
        clear = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        displayBox.setFont(new java.awt.Font("Ubuntu", 1, 36));
        displayBox.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        displayBox.setEditable(false);
        displayBox.addKeyListener(keyPress());

        btn[1].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[1].setText("1");
        btn[1].addKeyListener(keyPress());
        btn[1].setBackground(Color.WHITE);

        btn[2].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[2].setText("2");
        btn[2].addKeyListener(keyPress());
        btn[2].setBackground(Color.WHITE);

        btn[3].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[3].setText("3");
        btn[3].addKeyListener(keyPress());
        btn[3].setBackground(Color.WHITE);

        btn[4].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[4].setText("4");
        btn[4].addKeyListener(keyPress());
        btn[4].setBackground(Color.WHITE);

        btn[5].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[5].setText("5");
        btn[5].addKeyListener(keyPress());
        btn[5].setBackground(Color.WHITE);

        btn[6].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[6].setText("6");
        btn[6].addKeyListener(keyPress());
        btn[6].setBackground(Color.WHITE);

        btn[7].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[7].setText("7");
        btn[7].addKeyListener(keyPress());
        btn[7].setBackground(Color.WHITE);

        btn[8].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[8].setText("8");
        btn[8].addKeyListener(keyPress());
        btn[8].setBackground(Color.WHITE);

        btn[9].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[9].setText("9");
        btn[9].addKeyListener(keyPress());
        btn[9].setBackground(Color.WHITE);

        btn[0].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[0].setText("0");
        btn[0].addKeyListener(keyPress());
        btn[0].setBackground(Color.WHITE);

        op[0].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        op[0].setText("+");
        op[0].addKeyListener(keyPress());
        op[0].setBackground(Color.WHITE);

        op[1].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        op[1].setText("-");
        op[1].addKeyListener(keyPress());
        op[1].setBackground(Color.WHITE);

        op[2].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        op[2].setText("*");
        op[2].addKeyListener(keyPress());
        op[2].setBackground(Color.WHITE);

        op[3].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        op[3].setText("/");
        op[3].addKeyListener(keyPress());
        op[3].setBackground(Color.WHITE);

        clear.setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        clear.setText("AC");
        clear.addKeyListener(keyPress());
        clear.setBackground(Color.WHITE);

        // This is auto-generated part for GUI when creating GUI using netbeans
        // The code positions various buttons on the calculator and also their
        // properties.
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(displayBox, javax.swing.GroupLayout.PREFERRED_SIZE, 415, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                        .addGap(26, 26, 26)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(op[0], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(21, 21, 21)
                                .addComponent(op[1], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(op[2], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(op[3], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(btn[4], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(70, 70, 70)
                                        .addComponent(btn[5], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(btn[7], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(70, 70, 70)
                                        .addComponent(btn[8], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addComponent(btn[0], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addGroup(layout.createSequentialGroup()
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                            .addComponent(clear, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                            .addComponent(btn[1], javax.swing.GroupLayout.DEFAULT_SIZE, 91, Short.MAX_VALUE))
                                        .addGap(70, 70, 70)
                                        .addComponent(btn[2], javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                .addGap(72, 72, 72)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(btn[3], javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(btn[6], javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(btn[9], javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))))))
                .addContainerGap(28, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(21, 21, 21)
                .addComponent(displayBox, javax.swing.GroupLayout.PREFERRED_SIZE, 81, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(clear, javax.swing.GroupLayout.PREFERRED_SIZE, 73, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 36, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btn[1], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[2], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[3], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(32, 32, 32)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btn[6], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[5], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[4], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(35, 35, 35)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btn[8], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[7], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[9], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(33, 33, 33)
                .addComponent(btn[0], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(37, 37, 37)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(op[0], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(op[1], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(op[2], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(op[3], javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(24, 24, 24))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents
}
