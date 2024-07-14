import os
import tempfile
import unittest
from unittest.mock import MagicMock, patch

from typer.testing import CliRunner

from codecarbon import __app_name__, __version__
from codecarbon.cli.main import codecarbon

# MOCK API CLIENT


@patch("codecarbon.cli.main.ApiClient")
class TestApp(unittest.TestCase):
    def setUp(self):
        self.runner = CliRunner()
        self.mock_api_client = MagicMock()
        self.mock_api_client.get_list_organizations.return_value = [
            {"id": "1", "name": "test org Code Carbon"}
        ]
        self.mock_api_client.list_teams_from_organization.return_value = [
            {"id": "1", "name": "test team Code Carbon"}
        ]

        self.mock_api_client.list_projects_from_team.return_value = [
            {"id": "1", "name": "test project Code Carbon"}
        ]
        self.mock_api_client.list_experiments_from_project.return_value = [
            {"id": "1", "name": "test experiment Code Carbon"}
        ]
        self.mock_api_client.create_organization.return_value = {
            "id": "1",
            "name": "test org Code Carbon",
        }
        self.mock_api_client.create_team.return_value = {
            "id": "1",
            "name": "test team Code Carbon",
        }
        self.mock_api_client.create_project.return_value = {
            "id": "1",
            "name": "test project Code Carbon",
        }
        self.mock_api_client.add_experiment.return_value = {
            "id": "1",
            "name": "test experiment Code Carbon",
        }

    def test_app(self, MockApiClient):
        result = self.runner.invoke(codecarbon, ["--version"])
        self.assertEqual(result.exit_code, 0)
        self.assertIn(__app_name__, result.stdout)
        self.assertIn(__version__, result.stdout)

    @patch("codecarbon.cli.main.Confirm.ask")
    @patch("codecarbon.cli.main.questionary_prompt")
    def test_config_no_local_new_all(self, mock_prompt, mock_confirm, MockApiClient):
        temp_dir = os.getenv("RUNNER_TEMP", tempfile.gettempdir())
        temp_codecarbon_config = tempfile.NamedTemporaryFile(
            mode="w+t", delete=False, dir=temp_dir
        )

        MockApiClient.return_value = self.mock_api_client
        mock_prompt.side_effect = [
            "/tmp/.codecarbon.config",
            "Create New Organization",
            "Create New Project",
            "Create New Experiment",
        ]
        mock_confirm.side_effect = [True, False, False, False]

        result = self.runner.invoke(
            codecarbon,
            ["config"],
            input=f"{temp_codecarbon_config.name}\n",
        )
        self.assertEqual(result.exit_code, 0)
        self.assertIn(
            "Creating new experiment\nExperiment name : [Code Carbon user test]",
            result.stdout,
        )
        self.assertIn(
            "Consult configuration documentation for more configuration options",
            result.stdout,
        )

    @patch("codecarbon.cli.main.get_config")
    @patch("codecarbon.cli.main.questionary_prompt")
    def test_init_use_local(self, mock_prompt, mock_config, MockApiClient):
        mock_prompt.return_value = "~/.codecarbon.config"
        mock_config.return_value = {
            "api_endpoint": "http://localhost:8008",
            "organization_id": "114",
            "project_id": "133",
            "experiment_id": "yolo123",
        }
        result = self.runner.invoke(codecarbon, ["config"], input="n")
        self.assertEqual(result.exit_code, 0)
        self.assertIn(
            "Using already existing global config file ",
            result.stdout,
        )

    def custom_questionary_side_effect(*args, **kwargs):
        default_value = kwargs.get("default")
        return MagicMock(return_value=default_value)


if __name__ == "__main__":
    unittest.main()
