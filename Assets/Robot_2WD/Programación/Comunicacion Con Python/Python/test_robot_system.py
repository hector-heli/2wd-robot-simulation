import unittest
import numpy as np
from unittest.mock import MagicMock, patch
import sys
import os

# Import the classes to test
from pyPso import pso
from pyArduino import serialArduino

class TestPSO(unittest.TestCase):
    def setUp(self):
        # Simple sphere function for testing: minimize sum of squares
        def sphere_fn(x):
            return np.sum(x**2, axis=1)
        
        self.cost_fn = sphere_fn
        self.swarmsize = 10
        self.npar = 2
        self.optimizer = pso(self.cost_fn, self.swarmsize, self.npar)

    def test_pso_initialization(self):
        """Verify that the particles and velocities are initialized with correct shapes."""
        self.assertEqual(self.optimizer.x.shape, (self.swarmsize, self.npar))
        self.assertEqual(self.optimizer.v.shape, (self.swarmsize, self.npar))
        self.assertEqual(len(self.optimizer.cost), self.swarmsize)
        self.assertEqual(self.optimizer.gen, 0)
        self.assertIsNotNone(self.optimizer.globalbest)

    def test_pso_run_updates_generations(self):
        """Verify that running the PSO updates the generation counter and summary."""
        max_gen = 5
        self.optimizer.run(maxgen=max_gen)
        self.assertEqual(self.optimizer.gen, max_gen)
        self.assertEqual(len(self.optimizer.summary), max_gen)

class TestSerialArduino(unittest.TestCase):
    @patch('serial.Serial')
    def test_arduino_connection_params(self, mock_serial):
        """Verify that serial connection is opened with correct port and baud rate."""
        mock_conn = MagicMock()
        mock_serial.return_value = mock_conn
        
        test_port = 'COM_TEST'
        test_baud = 115200
        client = serialArduino(test_port, test_baud)
        
        mock_serial.assert_called_with(test_port, test_baud, timeout=10)

    @patch('serial.Serial')
    def test_send_data_formatting(self, mock_serial):
        """Verify that data sent to Arduino is correctly formatted as a comma-separated string."""
        mock_conn = MagicMock()
        mock_serial.return_value = mock_conn
        client = serialArduino('COM_TEST')
        
        test_data = [12.5, 45.0]
        client.sendData(test_data)
        
        mock_conn.write.assert_called_with(b'12.5,45.0\n')

if __name__ == '__main__':
    unittest.main()